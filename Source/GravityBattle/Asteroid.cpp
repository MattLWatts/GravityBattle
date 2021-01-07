// Fill out your copyright notice in the Description page of Project Settings.

#include "Asteroid.h"
#include "PlayerSpaceship.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    InitaliseComponents();

    speed = 250.0f;
    screenEdge = -1200.0f;
    asteroidDestroyCurrentTimer = 0.0f;
    asteroidDestroyTime = 2.0f;
    bIsDestroyed = false;
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

    StartingPosAndRot();

    asteroidDestroyedSound->Deactivate();

    // Add collision function
    OnActorBeginOverlap.AddDynamic(this, &AAsteroid::OnCollision);

    // Get player pointer
    playerRef = Cast<APlayerSpaceship>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AAsteroid::GetNewPosition(FVector* newPosition, float DeltaTime)
{
    // Checks for gravity being present
    if (playerRef->currentGravity > 0.5f)
    {
        // Calculates new position
        *newPosition = FVector(currPos.X + (DeltaTime * playerRef->currentGravity * (speed / 4)), currPos.Y, currPos.Z);
    }
    else
    {
        // Calculates new position
        *newPosition = FVector(currPos.X + (-speed * DeltaTime), currPos.Y, currPos.Z);
    }
}

void AAsteroid::StartingPosAndRot()
{
    currPos = FVector(1300.0f, FMath::RandRange(-350.0f, 350.0f), -30.0f);
    this->SetActorRotation(FRotator(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f)));
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bIsDestroyed == false) 
    {
        FVector newPosition;

        GetNewPosition(&newPosition, DeltaTime);

        // Checks if new position is out of screen range
        if (newPosition.X < screenEdge)
        {
            // Destroys actor
            this->Destroy();
        }

        // Gives bullet new position
        this->SetActorLocation(newPosition);

        // Sets location to new location
        currPos = newPosition;
    }
    else 
    {
        if (asteroidDestroyTime < asteroidDestroyCurrentTimer) 
        {
            this->Destroy();
        }
        else 
        {
            asteroidDestroyCurrentTimer += DeltaTime;
        }
    }
}

// Create and add components to actor
void AAsteroid::InitaliseComponents()
{
    // Create components
    RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
    asteroidCollider = CreateDefaultSubobject<UCapsuleComponent>("Asteroid Collider");
    asteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>("Asteroid Mesh");
    asteroidDestroyParticleEffect = CreateDefaultSubobject<UParticleSystemComponent>("Asteroid Particle Effect");
    asteroidDestroyedSound = CreateDefaultSubobject<UAudioComponent>("Asteroid Destroyed Sound");

    // Attach components to root
    asteroidCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    asteroidMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    asteroidDestroyParticleEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    asteroidDestroyedSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AAsteroid::OnCollision(AActor* asteroid, AActor* other)
{
    if (other != nullptr)
    {
        // Checks for bullet collision
        if (other->ActorHasTag("Bullet"))
        {
            other->Destroy();
            bIsDestroyed = true;
            asteroidDestroyedSound->Play();
            asteroidMesh->SetVisibility(false);
            this->SetActorEnableCollision(false);
        }
    }
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "PlayerSpaceship.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    InitialiseComponents();

    speed = 0.0f;
    screenEdge = 1200.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

    // Get starting position
    currPos = this->GetActorLocation();

    // Bind collision function
    OnActorBeginOverlap.AddDynamic(this, &ABullet::OnCollision);

    playerRef = Cast<APlayerSpaceship>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Calculates new position
    FVector newPos;

    if (playerRef->currentGravity > 0.5f)
    {
        newPos = FVector(currPos.X + (-speed / 4 * DeltaTime * (playerRef->currentGravity)), currPos.Y, currPos.Z);
    }
    else 
    {
        newPos = FVector(currPos.X + (speed * DeltaTime), currPos.Y, currPos.Z);
    }

    // Checks if new position isout of screen range
    if (newPos.X > screenEdge)
    {
        // Destroys actor
        this->Destroy();
    }

    // Gives bullet new position
    this->SetActorLocation(newPos);

    // Sets location to new location
    currPos = newPos;

}

// Create and add components to actor
void ABullet::InitialiseComponents()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
    bulletCollider = CreateDefaultSubobject<UCapsuleComponent>("Bullet Collider");
    bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");
    
    bulletCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    bulletMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Collision handling function
void ABullet::OnCollision(AActor* bullet, AActor* other)
{

}


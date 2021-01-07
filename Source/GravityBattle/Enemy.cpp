// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PlayerSpaceship.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    InitaliseComponents();
    enemyDestroyCurrentTimer = 0.0f;
    enemyDestroyTime = 2.0f;

    bIsDestroyed = false;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
    enemyDestroyedSound->Deactivate();
    enemyShootSound->Deactivate();

    OnActorBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);

    playerRef = Cast<APlayerSpaceship>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bIsDestroyed == false) 
    {
        currPos = this->GetActorLocation();
        playerPos = playerRef->GetActorLocation();

        // Move player into view and towards player
        if (currPos.Y != playerPos.Y)
        {
            newPosition.X = currPos.X - 850.0f;
            newPosition.Y = currPos.Y - playerPos.Y;
            newPosition.Z = 0.0f;
            newPosition.Normalize();
        }

        currPos -= newPosition * DeltaTime * speed;

        this->SetActorLocation(currPos);

        // Shoot bullet once delta has exceeded fire rate
        if (lastShotDelta > fireRate)
        {
            ShootBullet();
            lastShotDelta = 0.0f;
        }

        lastShotDelta += DeltaTime;
    }
    else 
    {
        // Allow the destroy sound to play before destroying object
        if (enemyDestroyTime < enemyDestroyCurrentTimer) 
        {
            this->Destroy();
        }
        else
        {
            enemyDestroyCurrentTimer += DeltaTime;
        }
    }

}

void AEnemy::InitaliseComponents()
{
    // Create sub components
    RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
    enemyHorizontalCollider = CreateDefaultSubobject<UCapsuleComponent>("Enemy Horizontal Collider");
    enemyVerticalCollider = CreateDefaultSubobject<UCapsuleComponent>("Enemy Vertical Collider");
    enemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Enemy Mesh");
    enemyDestroyedSound = CreateDefaultSubobject<UAudioComponent>("Enemy Destroyed Sound");
    enemyShootSound = CreateDefaultSubobject<UAudioComponent>("Enemy Shoot Sound");

    // Attach components to root
    enemyHorizontalCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    enemyVerticalCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    enemyMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    enemyDestroyedSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    enemyShootSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEnemy::ShootBullet()
{
    FActorSpawnParameters Params = {};
    Params.Owner = this;

    // Create bullet at enemies position
    AActor* bullet = GetWorld()->SpawnActor(bullet_BP, &currPos, NULL, Params);

    // Play shot sound
    enemyShootSound->Play();
}

void AEnemy::OnCollision(AActor* enemy, AActor* other)
{
    if (other != nullptr)
    {
        // Check for bullet collision
        // Destroy bullet and set boolean flag to true to start destroy sequence
        if (other->ActorHasTag("Bullet"))
        {
            other->Destroy();
            bIsDestroyed = true;
            enemyDestroyedSound->Play();
            enemyMesh->SetVisibility(false);
            this->SetActorEnableCollision(false);
        }
    }
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Bullet.h"

#include "Enemy.generated.h"

class APlayerSpaceship;

UCLASS()
class GRAVITYBATTLE_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* enemyMesh;

    UPROPERTY(EditAnywhere)
        UCapsuleComponent* enemyVerticalCollider;

    UPROPERTY(EditAnywhere)
        UCapsuleComponent* enemyHorizontalCollider;

    UPROPERTY(EditAnywhere)
        UAudioComponent* enemyDestroyedSound;

    UPROPERTY(EditAnywhere)
        UAudioComponent* enemyShootSound;

    // Bullet blueprint
    UPROPERTY(EditAnywhere)
        TSubclassOf<ABullet> bullet_BP;

    // Speed that enemy will move in the scene
    UPROPERTY(EditAnywhere)
        float speed;

    UPROPERTY(EditAnywhere)
        float fireRate;

    UFUNCTION()
        void OnCollision(AActor* enemy, AActor* other);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    // Current position of the enemy
    FVector currPos;
    // Current position of the player
    FVector playerPos;

    // New position vector
    FVector newPosition;

    // Create and add components to actor
    void InitaliseComponents();

    void ShootBullet();

    float lastShotDelta;

    // Timer for when enemy is destroyed
    float enemyDestroyTime;
    float enemyDestroyCurrentTimer;

    bool bIsDestroyed;

    APlayerSpaceship* playerRef;
};

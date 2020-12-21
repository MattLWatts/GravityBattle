// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "DefaultEndlessGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Bullet.h"

#include "PlayerSpaceship.generated.h"

UCLASS()
class GRAVITYBATTLE_API APlayerSpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerSpaceship();

    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* playerMesh;

    UPROPERTY(EditAnywhere)
        UCapsuleComponent* playerColliderVertical;

    UPROPERTY(EditAnywhere)
        UCapsuleComponent* playerColliderHorizontal;

    UPROPERTY(EditAnywhere)
        UAudioComponent* playerDamageSound;

    UPROPERTY(EditAnywhere)
        UAudioComponent* playerShootSound;



    // Horizontal bounds which the player cannot exceed
    UPROPERTY(EditAnywhere)
        float playerHorizontalBounds;

    // Vertical bounds which the player cannot exceed
    UPROPERTY(EditAnywhere)
        float playerVerticalBounds;

    // Players maximum health
    UPROPERTY(BlueprintReadOnly)
        float maxHealth;

    // Players current health
    UPROPERTY(BlueprintReadOnly)
        float currentHealth;

    UPROPERTY(BlueprintReadOnly)
        int seconds;
    UPROPERTY(BlueprintReadOnly)
        int minutes;

    UPROPERTY(BlueprintReadWrite)
        bool hasAccel;

    // Movement speed across each axis
    UPROPERTY(BlueprintReadWrite)
        float verticalVelocity;
    UPROPERTY(BlueprintReadWrite)
        float horizontalVelocity;

    // Bullet blueprint which is spawned when player shoots
    UPROPERTY(EditAnywhere)
        TSubclassOf<ABullet> bullet_BP;

    // Collision detection function
    UFUNCTION()
        void OnCollision(AActor* player, AActor* other);

    UPROPERTY(BlueprintReadWrite)
        float currentGravity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

    // Players current score
    int playerScore;

    // Players current and new position
    FVector currentPos;
    FVector newPos;

    // Player is holding down shoot button = true
    bool bIsShooting;
    // Time gap between bullets
    float weaponFireRate;
    // Current time since last bullet was fired
    float lastShotDelta;

    bool bCollision;
    bool bDead;

    float gameTimer;

    // Called on start to create and attach components
    void InitialiseComponents();

    // Called to shoot a bullet
    void ShootBullet();

    // Sets shooting to true
    void StartShooting();

    // Sets shooting to false
    void FinishShooting();

    void FormatTimerUI();
};

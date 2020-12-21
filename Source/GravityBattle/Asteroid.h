// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

#include "Asteroid.generated.h"

class APlayerSpaceship;

UCLASS()
class GRAVITYBATTLE_API AAsteroid : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAsteroid();

    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* asteroidMesh;

    UPROPERTY(EditAnywhere)
        UCapsuleComponent* asteroidCollider;

    UPROPERTY(EditAnywhere)
        UAudioComponent* asteroidDestroyedSound;

    UPROPERTY(EditAnywhere)
        UParticleSystemComponent* asteroidDestroyParticleEffect;

    // X coordinate where asteroid will be deleted once crossed
    UPROPERTY(EditAnywhere)
        float screenEdge;

    // Speed that asteroid will cross the scene
    UPROPERTY(EditAnywhere)
        float speed;

    UFUNCTION()
        void OnCollision(AActor* asteroid, AActor* other);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void GetNewPosition(FVector* newPosition, float DeltaTime);

    virtual void StartingPosAndRot();

    // Current position of the asteroid
    FVector currPos;

    // Create and add components to actor
    void InitaliseComponents();

    float asteroidDestroyTime;
    float asteroidDestroyCurrentTimer;

    bool bIsDestroyed;

    APlayerSpaceship* playerRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

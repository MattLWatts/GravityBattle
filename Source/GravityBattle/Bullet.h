// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"

#include "Bullet.generated.h"

class APlayerSpaceship;

UCLASS()
class GRAVITYBATTLE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* bulletMesh;

    UPROPERTY(EditAnywhere)
        UCapsuleComponent* bulletCollider;

    // Bullet speed
    UPROPERTY(EditAnywhere)
        float speed;

    // Collision handling function
    UFUNCTION()
        void OnCollision(AActor* bullet, AActor* other);

    // Current position of the bullet
    FVector currPos;

    // Bullet destroyed after its x position exceeds screenEdge
    UPROPERTY(EditAnywhere)
        float screenEdge;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    // Create and add components to actor
    void InitialiseComponents();

    APlayerSpaceship* playerRef;
};

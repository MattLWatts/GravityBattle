// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asteroid.h"
#include "SpinningAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYBATTLE_API ASpinningAsteroid : public AAsteroid
{
	GENERATED_BODY()

private:
    virtual void GetNewPosition(FVector* newPosition, float DeltaTime) override;

    virtual void StartingPosAndRot() override;

    float angle;

    FVector directionVector;
};

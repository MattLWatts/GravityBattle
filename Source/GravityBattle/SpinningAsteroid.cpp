// Fill out your copyright notice in the Description page of Project Settings.

#include "SpinningAsteroid.h"
#include "PlayerSpaceship.h"

void ASpinningAsteroid::StartingPosAndRot()
{
    // Get Tan of the angle to give direction vector
    angle = FMath::DegreesToRadians(FMath::RandRange(-25.0f,25.0f));
    directionVector = FVector(FMath::Cos(angle), FMath::Sin(angle), 0.0f);

    if (angle > 0)
    {
        currPos = FVector(1250.0f, 350.0f, 0.0f);
    }
    else 
    {
        currPos = FVector(1250.0f, -350.0f, 0.0f);
    }

    this->SetActorRotation(FRotator(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f)));
}

void ASpinningAsteroid::GetNewPosition(FVector* newPosition, float DeltaTime)
{
    if (playerRef->currentGravity > 0.5f)
    {
        *newPosition = FVector(currPos.X + (DeltaTime * playerRef->currentGravity * (speed / 4)), currPos.Y, currPos.Z);
    }
    else 
    {
        *newPosition = currPos - (directionVector * speed * DeltaTime);
    }
}
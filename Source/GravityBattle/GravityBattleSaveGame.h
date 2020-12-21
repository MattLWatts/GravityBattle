// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "Kismet/GameplayStatics.h"

#include "GravityBattleSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYBATTLE_API UGravityBattleSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UGravityBattleSaveGame();

    UPROPERTY(EditAnywhere)
        int playerHighscore;

    UPROPERTY(VisibleAnywhere, Category = UserData)
        FString saveName;

    UPROPERTY(VisibleAnywhere, Category = UserData)
        FString saveIndex;
};

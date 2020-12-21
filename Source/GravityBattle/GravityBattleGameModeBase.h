// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GravityBattleSaveGame.h"
#include "GameFramework/GameModeBase.h"
#include "GravityBattleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYBATTLE_API AGravityBattleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    AGravityBattleGameModeBase();

    UFUNCTION(BlueprintCallable)
        void LoadGame();

    UFUNCTION(BlueprintCallable)
        void ResetHighscore();

    UPROPERTY(BlueprintReadOnly)
        int highscore;

};

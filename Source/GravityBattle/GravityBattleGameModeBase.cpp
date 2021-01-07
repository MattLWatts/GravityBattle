// Copyright Epic Games, Inc. All Rights Reserved.


#include "GravityBattleGameModeBase.h"

AGravityBattleGameModeBase::AGravityBattleGameModeBase()
{
    highscore = 0;
}

void AGravityBattleGameModeBase::LoadGame()
{
    // Check if load game exists
    // Necessairy check for android builds because otherwise it causes a crash :(
    if (UGravityBattleSaveGame* loadGame = Cast<UGravityBattleSaveGame>(UGameplayStatics::LoadGameFromSlot("DefaultSave", 0)))
    {
        // Load highscore into variable. Called in blueprint
        highscore = loadGame->playerHighscore;
    }
}

void AGravityBattleGameModeBase::ResetHighscore()
{
    // Create save game
    UGravityBattleSaveGame* saveGame = Cast<UGravityBattleSaveGame>(UGameplayStatics::CreateSaveGameObject(UGravityBattleSaveGame::StaticClass()));
    
    saveGame->playerHighscore = 0;

    // Save over current slot
    UGameplayStatics::SaveGameToSlot(saveGame, "DefaultSave", 0);
}
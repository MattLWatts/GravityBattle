// Copyright Epic Games, Inc. All Rights Reserved.


#include "GravityBattleGameModeBase.h"

AGravityBattleGameModeBase::AGravityBattleGameModeBase()
{
    highscore = 0;
}

void AGravityBattleGameModeBase::LoadGame()
{
    if (UGravityBattleSaveGame* loadGame = Cast<UGravityBattleSaveGame>(UGameplayStatics::LoadGameFromSlot("DefaultSave", 0)))
    {
        highscore = loadGame->playerHighscore;
    }
}

void AGravityBattleGameModeBase::ResetHighscore()
{
    UGravityBattleSaveGame* saveGame = Cast<UGravityBattleSaveGame>(UGameplayStatics::CreateSaveGameObject(UGravityBattleSaveGame::StaticClass()));

    saveGame->playerHighscore = 0;

    UGameplayStatics::SaveGameToSlot(saveGame, "DefaultSave", 0);
}
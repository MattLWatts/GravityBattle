// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultEndlessGamemode.h"

ADefaultEndlessGamemode::ADefaultEndlessGamemode()
{

    // Initialise timer to 0
    gameTimer = 0.0f;

    asteroidSpawnInterval = 2.0f;
    asteroidSpawnTime = 2.0f;

    backgroundMusic = CreateDefaultSubobject<UAudioComponent>("Background Music");
    backgroundMusic->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    asteroidSpawnPos = FVector(1300.0f, 0.0f, 0.0f);
    asteroidSpawnRot = FRotator(0.0f, 0.0f, 0.0f);

    currentWorld = GetWorld();

    gameScore = 0;
}

void ADefaultEndlessGamemode::BeginPlay()
{
    Super::BeginPlay();

    backgroundMusic->Play();

    bIsPlayerAlive = true;

    if (inGameUIClass != nullptr)
    {
        inGameUI = CreateWidget<UUserWidget>(GetWorld(), inGameUIClass);
        inGameUI->AddToViewport();
    }

    if (endScreenUIClass != nullptr)
    {
        endScreenUI = CreateWidget<UUserWidget>(GetWorld(), endScreenUIClass);
        endScreenUI->AddToViewport();
        endScreenUI->SetVisibility(ESlateVisibility::Hidden);
    }

    playerReference = GetWorld()->GetFirstPlayerController();
}

void ADefaultEndlessGamemode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsPlayerAlive == false)
    {
        endScreenUI->SetVisibility(ESlateVisibility::Visible);
        bIsPlayerAlive = true;

        SaveGame();

        APlayerController* const player = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

        player->SetPause(true);
    }

    // Check if asteroid can be spawned
    if (asteroidSpawnTime < gameTimer)
    {
        // Spawn asteroid
        SpawnAsteroid();

        // Increment timer by spawn interval
        asteroidSpawnTime = gameTimer + asteroidSpawnInterval;
    }

    if (spinningAsteroidSpawnTime < gameTimer) 
    {
        SpawnSpinningAsteroid();

        spinningAsteroidSpawnTime = gameTimer + asteroidSpawnInterval;
    }

    gameTimer += DeltaTime;

}

void ADefaultEndlessGamemode::SaveGame()
{
    UGravityBattleSaveGame* saveGame = Cast<UGravityBattleSaveGame>(UGameplayStatics::CreateSaveGameObject(UGravityBattleSaveGame::StaticClass()));

    if (saveGame->playerHighscore < gameScore)
    {
        saveGame->playerHighscore = gameScore;

        UGameplayStatics::SaveGameToSlot(saveGame, "DefaultSave", 0);
    }
}

void ADefaultEndlessGamemode::SpawnAsteroid()
{
    // Get random index of next model to spawn in
    asteroidIndex = FMath::RandRange(0, 4);

    // Spawn asteroid
    AActor* newAsteroid = GetWorld()->SpawnActor(asteroidArray[asteroidIndex], &asteroidSpawnPos, &asteroidSpawnRot, asteroidParams);
}

void ADefaultEndlessGamemode::SpawnSpinningAsteroid()
{
    // Spawn asteroid
    AActor* newSpinningAsteroid = GetWorld()->SpawnActor(spinningAsteroid, &asteroidSpawnPos, &asteroidSpawnRot, asteroidParams);
}

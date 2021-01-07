// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultEndlessGamemode.h"

ADefaultEndlessGamemode::ADefaultEndlessGamemode()
{

    // Initialise timer to 0
    gameTimer = 0.0f;

    asteroidSpawnInterval = 2.0f;
    asteroidSpawnTime = 2.0f;

    enemySpawnTime = 4.0f;
    enemySpawnTimeInterval = 20.0f;

    backgroundMusic = CreateDefaultSubobject<UAudioComponent>("Background Music");
    backgroundMusic->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    asteroidSpawnPos = FVector(1300.0f, 0.0f, -30.0f);
    asteroidSpawnRot = FRotator(0.0f, 0.0f, 0.0f);

    currentWorld = GetWorld();

    gameScore = 0;
}

void ADefaultEndlessGamemode::BeginPlay()
{
    Super::BeginPlay();

    // Start music
    backgroundMusic->Play();

    bIsPlayerAlive = true;

    // Setup UI Elements
    if (inGameUIClass != nullptr)
    {
        inGameUI = CreateWidget<UUserWidget>(GetWorld(), inGameUIClass);
        inGameUI->AddToViewport();
    }

    // Hide endscreen
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

    // Check if player is alive
    if (bIsPlayerAlive == false)
    {
        // Make end screen visible
        endScreenUI->SetVisibility(ESlateVisibility::Visible);

        bIsPlayerAlive = true;

        // Save the game
        SaveGame();

        // Get and pause player
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

        if (spinningAsteroidSpawnInterval > 0.4f)
        {
            spinningAsteroidSpawnInterval -= 0.02f;
        }
    }

    if (spinningAsteroidSpawnTime < gameTimer) 
    {
        SpawnSpinningAsteroid();

        spinningAsteroidSpawnTime = gameTimer + spinningAsteroidSpawnInterval;

        if (spinningAsteroidSpawnInterval > 0.3f) 
        {
            spinningAsteroidSpawnInterval -= 0.02f;
        }
    }

    if (enemySpawnTime < gameTimer) 
    {
        SpawnEnemy();

        enemySpawnTime = gameTimer + enemySpawnTimeInterval;
    }

    // Increment timer every tick
    gameTimer += DeltaTime;

}

void ADefaultEndlessGamemode::SaveGame()
{
    // Create save gane
    UGravityBattleSaveGame* saveGame = Cast<UGravityBattleSaveGame>(UGameplayStatics::CreateSaveGameObject(UGravityBattleSaveGame::StaticClass()));

    // Check if the score achieved is higher than the current one stored
    if (saveGame->playerHighscore < gameScore)
    {
        saveGame->playerHighscore = gameScore;
        // Save in slot 0 with name "Default SAve)
        UGameplayStatics::SaveGameToSlot(saveGame, "DefaultSave", 0);
    }
}

void ADefaultEndlessGamemode::SpawnAsteroid()
{
    // Get random index of next model to spawn in
    asteroidIndex = FMath::RandRange(0, 4);

    // Spawn asteroid
    AActor* newAsteroid = GetWorld()->SpawnActor(asteroidArray[asteroidIndex], &asteroidSpawnPos, &asteroidSpawnRot, spawnParams);
}

void ADefaultEndlessGamemode::SpawnSpinningAsteroid()
{
    // Spawn asteroid
    AActor* newSpinningAsteroid = GetWorld()->SpawnActor(spinningAsteroid, &asteroidSpawnPos, &asteroidSpawnRot, spawnParams);
}

void ADefaultEndlessGamemode::SpawnEnemy()
{
    newEnemy = GetWorld()->SpawnActor(enemyShip, new FVector(1100.0f, 0.0f, 40.0f), &asteroidSpawnRot, spawnParams);
}

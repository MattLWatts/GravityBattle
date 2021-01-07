// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Components/AudioComponent.h"
#include "Asteroid.h"
#include "SpinningAsteroid.h"
#include "GravityBattleSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Enemy.h"

#include "DefaultEndlessGamemode.generated.h"

/**
 *
 */
UCLASS()
class GRAVITYBATTLE_API ADefaultEndlessGamemode : public AGameMode
{
    GENERATED_BODY()

public:
    // Constructor
    ADefaultEndlessGamemode();

    // Asteroid and enemy objects to be spawned in
    UPROPERTY(EditAnywhere)
        TSubclassOf<AAsteroid> asteroidArray[5];

    UPROPERTY(EditAnywhere)
        TSubclassOf<ASpinningAsteroid> spinningAsteroid;

    UPROPERTY(EditAnywhere)
        TSubclassOf<AEnemy> enemyShip;



    UPROPERTY(EditAnywhere)
        UAudioComponent* backgroundMusic;


    // Timers used in the spawning of each asteroid/enemy

    UPROPERTY(EditAnywhere)
        float asteroidSpawnInterval;

    UPROPERTY(EditAnywhere)
        float spinningAsteroidSpawnInterval;

    UPROPERTY(EditAnywhere)
        float asteroidSpawnTime;

    UPROPERTY(EditAnywhere)
        float spinningAsteroidSpawnTime;

    UPROPERTY(EditAnywhere)
        float enemySpawnTime;

    UPROPERTY(EditAnywhere)
        float enemySpawnTimeInterval;

    // UI Elements

    UPROPERTY(EditAnywhere, Category = "HUD")
        TSubclassOf<UUserWidget> inGameUIClass;
    UUserWidget* inGameUI;

    UPROPERTY(EditAnywhere, Category = "HUD")
        TSubclassOf<UUserWidget> endScreenUIClass;
    UUserWidget* endScreenUI;

    // Final game score
    UPROPERTY(BlueprintReadOnly)
        int gameScore;

    UPROPERTY(BlueprintReadWrite)
        FString playerName;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    bool bIsPlayerAlive;

private:

    // Asteroid spawn location
    FVector asteroidSpawnPos;
    FRotator asteroidSpawnRot;

    void SaveGame();

    FActorSpawnParameters spawnParams;

    // Current game time
    float gameTimer;

    UWorld* currentWorld;

    int asteroidIndex;

    // Enemy spawning functions
    void SpawnAsteroid();

    void SpawnSpinningAsteroid();

    void SpawnEnemy();

    APlayerController* playerReference;

    AActor* newEnemy;
};

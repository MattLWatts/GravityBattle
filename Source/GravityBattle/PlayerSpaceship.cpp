// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"

// Sets default values
APlayerSpaceship::APlayerSpaceship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Setup components
    InitialiseComponents();

    // Initialise local variables
    verticalVelocity = 0.0f;
    horizontalVelocity = 0.0f;
    bIsShooting = false;
    weaponFireRate = 0.25f;
    lastShotDelta = 0.0f;
    playerScore = 0.0f;
    currentGravity = 0.0f;
}

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();
	
    // Get starting position & rotation
    currentPos = this->GetActorLocation();

    // Initialise variables
    bCollision = false;
    bDead = false;
    maxHealth = 100.0f;
    currentHealth = 100.0f;

    seconds = 0;
    minutes = 0;

    // Deactivate components
    playerDamageSound->Deactivate();
    playerShootSound->Deactivate();

    // Bind collision function
    OnActorBeginOverlap.AddDynamic(this, &APlayerSpaceship::OnCollision);
}

// Called every frame
void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (currentHealth <= 0 && bDead == false)
    {
        // Get reference to gamemode
        ADefaultEndlessGamemode* GamemodePtr = Cast<ADefaultEndlessGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
        
        //Set player to dead
        GamemodePtr->bIsPlayerAlive = false;
        playerScore = StaticCast<int>(seconds + (minutes * 60));
        GamemodePtr->gameScore = playerScore;
        bDead = true;
    }

    // Check if velocity is not 0
    if (verticalVelocity != 0.0f || horizontalVelocity != 0.0f)
    {
        
        float xValue = currentPos.X;
        float yValue = currentPos.Y;

        // Check virtical bounds to see if movement is legal
        if (currentPos.X + (verticalVelocity * DeltaTime) < playerVerticalBounds &&
            currentPos.X + (verticalVelocity * DeltaTime) > -playerVerticalBounds)
        {
            xValue = currentPos.X + (verticalVelocity * DeltaTime);
        }

        // Check horzontal bounds to see if movement is legal
        if (currentPos.Y + (horizontalVelocity * DeltaTime) < playerHorizontalBounds &&
            currentPos.Y + (horizontalVelocity * DeltaTime) > -playerHorizontalBounds) 
        {
            yValue = currentPos.Y + (horizontalVelocity * DeltaTime);
        }
        
        
        // Calculate new position using velocity
        newPos = FVector(xValue, yValue, 0.0f);

        // Move actor to new position
        this->SetActorLocation(newPos);

        // Update player location
        currentPos = newPos;
    }

    // Check if player is pressing shoot button
    if (bIsShooting == true)
    {
        // Check if last shot has exceeded the fire rate
        if (lastShotDelta > weaponFireRate)
        {
            // Call function to create bullet
            ShootBullet();
            // Reset bullet delta
            lastShotDelta = 0.0f;
        }
    }

    // Increment the delta by the frame time
    lastShotDelta += DeltaTime;

    gameTimer += DeltaTime;
    FormatTimerUI();
}

// Called to bind functionality to input
void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction(FName("Shoot"), IE_Pressed, this, &APlayerSpaceship::StartShooting);

    PlayerInputComponent->BindAction(FName("Shoot"), IE_Released, this, &APlayerSpaceship::FinishShooting);

}

// Called on start to create and attach components
void APlayerSpaceship::InitialiseComponents() 
{
    // Create and attach components to 
    RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
    playerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Player Mesh");
    playerColliderVertical = CreateDefaultSubobject<UCapsuleComponent>("Player Collider Vertical");
    playerColliderHorizontal = CreateDefaultSubobject<UCapsuleComponent>("Player Collider Horizontal");
    playerDamageSound = CreateDefaultSubobject<UAudioComponent>("Player Damaged Sound");
    playerShootSound = CreateDefaultSubobject<UAudioComponent>("Player Shooting Sound");

    // Keep transform relative to parent (PlayerSpaceship)
    playerMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    playerColliderVertical->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    playerColliderHorizontal->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    playerDamageSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    playerShootSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called to shoot a bullet
void APlayerSpaceship::ShootBullet()
{

    FActorSpawnParameters Params = {};
    Params.Owner = this;

    AActor* bullet = GetWorld()->SpawnActor(bullet_BP, &currentPos, NULL,  Params);

    // Play shot sound
    playerShootSound->Play();

}

// Sets shooting to true
void APlayerSpaceship::StartShooting()
{
    bIsShooting = true;
}

// Sets shooting to false
void APlayerSpaceship::FinishShooting()
{
    bIsShooting = false;
}

void APlayerSpaceship::FormatTimerUI()
{
    seconds = static_cast<int>(gameTimer);

    if (seconds > 60)
    {
        seconds -= 60;
        gameTimer -= 60.0f;
        minutes += 1;
    }
}

void APlayerSpaceship::OnCollision(AActor* player, AActor* other)
{
    if (other != nullptr)
    {
        if (other->ActorHasTag("Asteroid"))
        {
            // Decrease health
            other->Destroy();
            playerDamageSound->Play();
            currentHealth -= 10;
        }
        if (other->ActorHasTag("SpinningAsteroid"))
        {
            // Decrease health
            other->Destroy();
            playerDamageSound->Play();
            currentHealth -= 5;
        }
    }
}
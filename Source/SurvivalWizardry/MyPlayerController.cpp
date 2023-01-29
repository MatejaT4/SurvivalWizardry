// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
// Called to bind functionality to input
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("UpDown"), this, &AMyPlayerController::MoveUpDown);
    InputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPlayerController::MoveLeftRight);
}

void AMyPlayerController::MoveUpDown(float Value)
{
	FRotator Rotation = GetPawn()->GetActorRotation();
	Rotation.Pitch = 0.f;
	Rotation.Yaw = 0.f;
	FVector WorldDirection = UKismetMathLibrary::GetForwardVector(Rotation);
	GetPawn()->AddMovementInput(WorldDirection, Value);
}

void AMyPlayerController::MoveLeftRight(float Value)
{
	FRotator Rotation = GetPawn()->GetActorRotation();
	Rotation.Pitch = 0.f;
	Rotation.Yaw = 0.f;
	FVector WorldDirection = UKismetMathLibrary::GetRightVector(Rotation);
	GetPawn()->AddMovementInput(WorldDirection, Value);
}


void AMyPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	
    if(bPlayerEnabled)
    {
        EnableInput(this);
    }
    else
    {
        DisableInput(this);
    }
    // bShowMouseCursor = bPlayerEnabled;
}

// void AMyPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
// {
// 	Super::GameHasEnded(EndGameFocus, bIsWinner);
// 	UE_LOG(LogTemp, Display, TEXT("Game has finished"));
// 	//GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);	
// }
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// HUD = CreateWidget(this, MyHUDClass);
	// if (HUD != nullptr) HUD->AddToViewport();
}
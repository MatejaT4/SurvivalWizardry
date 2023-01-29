// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALWIZARDRY_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void SetupInputComponent() override;
	void SetPlayerEnabledState(bool bPlayerEnabled);
	// virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
private:
//character movement
	void MoveUpDown(float Value);
	void MoveLeftRight(float Value);
	// UPROPERTY(EDitAnywhere)
	// float RestartDelay=4.f;
	// FTimerHandle RestartTimerHandle;
	
//widgets
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MyHUDClass;
	UPROPERTY()
	UUserWidget *HUD;
};

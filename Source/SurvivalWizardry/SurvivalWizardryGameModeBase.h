// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalWizardryGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALWIZARDRY_API ASurvivalWizardryGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:	
	ASurvivalWizardryGameModeBase();

	// Events
	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void StartGameCountdownEvent();

	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void StartGameEvent();

	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void EndGameEvent(bool bGameWon);

	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void LevelUpEvent();
	
	// public methods
	void ActorDied(AActor* DeadActor);

	void AddExperience(float Exp);

protected:
	virtual void BeginPlay() override;

private:
	// Properties we can set in editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AExpPickuble> ExpPickubleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience", meta = (AllowPrivateAccess = "true"))
	float ExperienceForNextLevel = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration of Game", meta = (AllowPrivateAccess = "true"))
	int32 GameLengthMinutes=1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration of Game", meta = (AllowPrivateAccess = "true"))
	int32 GameLengthSeconds=59;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration of Game", meta = (AllowPrivateAccess = "true"))
	int32 GameCountdownLength=3;

	// Blueprint callable methods
	UFUNCTION(BlueprintPure)
	int32 GetMinutes();

	UFUNCTION(BlueprintPure)
	int32 GetSeconds();

	UFUNCTION(BlueprintPure)
	float GetExperiencePercent() const;

	UFUNCTION(BlueprintPure)
	int GetCurrentLevel() const;

	// Private methods
	void EndGame(bool IsVictorious);

	void StartGame();

	void StartGameCountdown();

	void Clock();


	// Private properties
	UPROPERTY()
	class AWizard* Wizard;

	UPROPERTY()
	class AMyPlayerController* MyPlayerController;
	
	UPROPERTY()
	UWorld* World;

	UPROPERTY()
	FTimerHandle CountdownTimerHandle;

	UPROPERTY()
	FTimerHandle MatchTimerHandle;

	int32 minutes=0;

	int32 seconds=0;

	float CurrentExperience = 0.f;

	int level = 1;

};

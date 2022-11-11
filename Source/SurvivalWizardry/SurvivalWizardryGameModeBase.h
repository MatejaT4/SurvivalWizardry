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

	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void StartSpawningEvent();
	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void StopSpawningEvent();
	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void StartGameEvent();
	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void StartGameCountdownEvent();
	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void EndGameEvent(bool bGameWon);
	UFUNCTION(BlueprintImplementableEvent, Category="CppEvents")
	void LevelUpEvent();
	void AddExperience(float Exp);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class AWizard* Wizard;

	UPROPERTY()
	class AMyPlayerController* MyPlayerController;
	void GameEnded(bool IsVictorious);
	UPROPERTY()
	UWorld* World;

	void StartGame(bool bStart);
	void StartGameCountdown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experienc", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AExpPickuble> ExpPickubleClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experienc", meta = (AllowPrivateAccess = "true"))
	float CurrentExperience = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experienc", meta = (AllowPrivateAccess = "true"))
	float ExperienceForNextLevel = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experienc", meta = (AllowPrivateAccess = "true"))
	int level = 1;
	UFUNCTION(BlueprintPure)
	float GetExperiencePercent() const;
	UFUNCTION(BlueprintPure)
	int GetCurrentLevel() const;

	UPROPERTY()
	FTimerHandle TimerHandle;
	void Clock();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration of Game", meta = (AllowPrivateAccess = "true"))
	int32 minutes=1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration of Game", meta = (AllowPrivateAccess = "true"))
	int32 seconds=59;

	UFUNCTION(BlueprintPure)
	int32 GetMinutes();
	UFUNCTION(BlueprintPure)
	int32 GetSeconds();
};

// Copyright Epic Games, Inc. All Rights Reserved.


#include "SurvivalWizardryGameModeBase.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Wizard.h"
#include "MyPlayerController.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Spawner.h"
#include "ExpPickuble.h"
#include "Engine/DataTable.h"
#include "SpellStructure.h"

ASurvivalWizardryGameModeBase::ASurvivalWizardryGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASurvivalWizardryGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if(MyPlayerController)
    {
        MyPlayerController->SetPlayerEnabledState(false);  
    }
    Wizard = Cast<AWizard>(UGameplayStatics::GetPlayerPawn(this,0));
	World = GetWorld();
    minutes = GameLengthMinutes;
    seconds = GameLengthSeconds;
    StartGameCountdown();
}

void ASurvivalWizardryGameModeBase::StartGameCountdown()
{
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ASurvivalWizardryGameModeBase::StartGame, GameCountdownLength, false);	
    StartGameCountdownEvent();
}

void ASurvivalWizardryGameModeBase::StartGame()
{
	MyPlayerController->SetPlayerEnabledState(true);
    Wizard->HandleGameStart();
    GetWorldTimerManager().SetTimer(MatchTimerHandle, this, &ASurvivalWizardryGameModeBase::Clock, 1.0, true);	
    StartGameEvent();
}

void ASurvivalWizardryGameModeBase::Clock()
{
    if(minutes==0 && seconds==0)
    {
        GetWorldTimerManager().ClearTimer(MatchTimerHandle);
        EndGame(true);
    }
    else
    {
        if(seconds==0)
        {
            seconds=59;
            --minutes;
        }
        else
        {
            --seconds;    
        }
    }
}

int32 ASurvivalWizardryGameModeBase::GetSeconds()
{
    return seconds;
}

int32 ASurvivalWizardryGameModeBase::GetMinutes()
{
    return minutes;
}

void ASurvivalWizardryGameModeBase::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Wizard)
    {
        EndGame(false);
    }
    else if (AEnemyBase* DeadEnemy = Cast<AEnemyBase>(DeadActor))
    {
        FVector Location= DeadEnemy->GetActorLocation();
		FRotator Rotation = DeadEnemy->GetActorRotation();
        Location.Z = 40.f;
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AExpPickuble* experience = Cast<AExpPickuble>(World->SpawnActor(ExpPickubleClass, &Location, &Rotation, params));
        if(experience) experience->Exp = DeadEnemy->Experience;
        DeadEnemy->HandleDestruction();
    }
}

void ASurvivalWizardryGameModeBase::AddExperience(float Exp)
{
    CurrentExperience+=Exp;
    if(CurrentExperience>=ExperienceForNextLevel)
    {
        CurrentExperience -= ExperienceForNextLevel;
        ExperienceForNextLevel = ExperienceForNextLevel + ExperienceForNextLevel*0.5;
        ++level;
        LevelUpEvent();
    }
}

float ASurvivalWizardryGameModeBase::GetExperiencePercent() const
{
	return CurrentExperience / ExperienceForNextLevel;
}

int ASurvivalWizardryGameModeBase::GetCurrentLevel() const
{
	return level;
}

void ASurvivalWizardryGameModeBase::EndGame(bool IsVictorious)
{
    Wizard->HandleGameEnd(IsVictorious);

    if(MyPlayerController)
    {
        MyPlayerController->SetPlayerEnabledState(false);
    }
    if(IsVictorious==false)
    {
        EndGameEvent(false);
    }
    else{
        EndGameEvent(true);
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundActors);
        for(int i = 0; i < FoundActors.Num(); ++i)
        {
            FoundActors[i]->Destroy();
        }
    }
}
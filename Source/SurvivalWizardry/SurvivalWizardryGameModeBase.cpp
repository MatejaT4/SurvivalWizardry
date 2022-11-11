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
	PrimaryActorTick.bCanEverTick = true;
}

void ASurvivalWizardryGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//inicijalizacija
	MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	Wizard = Cast<AWizard>(UGameplayStatics::GetPlayerPawn(this,0));
	World = GetWorld();
    StartGameCountdown();
}

void ASurvivalWizardryGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASurvivalWizardryGameModeBase::StartGameCountdown()
{
	if(MyPlayerController)
    {
        MyPlayerController->SetPlayerEnabledState(false);    
        StartGameCountdownEvent();
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(this, &ASurvivalWizardryGameModeBase::StartGame, true);
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, 4, false);
    }
}

void ASurvivalWizardryGameModeBase::StartGame(bool bStart)
{
	MyPlayerController->SetPlayerEnabledState(bStart);
    Wizard->HandleGameStart();
	StartSpawningEvent();
    StartGameEvent();
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ASurvivalWizardryGameModeBase::Clock, 1.0, true);	
}

void ASurvivalWizardryGameModeBase::Clock()
{
    if(minutes==0 && seconds==0)
    {
        GetWorldTimerManager().ClearTimer(TimerHandle);
        GameEnded(true);
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
        GameEnded(false);
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

void ASurvivalWizardryGameModeBase::GameEnded(bool IsVictorious)
{
    Wizard->HandleGameEnd(true);
    StopSpawningEvent();
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
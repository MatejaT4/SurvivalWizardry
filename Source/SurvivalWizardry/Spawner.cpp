// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Wizard.h"
#include "Engine/World.h"
#include "HealthPack.h"

#define PI (3.1415926535897932f)
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	Wizard = Cast<AWizard>(UGameplayStatics::GetPlayerPawn(this,0));
	World = GetWorld();
}

void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::SpawnInArena(UClass* SpawningType,  float SpawnHeight)
{
	if(SpawningType == nullptr){
		return;
	}
	if(Wizard == nullptr){
		return;
	}
	if(World)
	{
		FVector Location;
		FRotator Rotation = FRotator::ZeroRotator;
		Location.X += FMath::RandRange(ArenaBottomLeftX, ArenaBottomLeftX + ArenaLengthX);
		Location.Y += FMath::RandRange(ArenaBottomLeftY, ArenaBottomLeftY + ArenaLengthY);
		Location.Z = SpawnHeight;
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		World->SpawnActor(SpawningType, &Location, &Rotation, params);
	}
}


void ASpawner::SpawnOnCircleAroundWizard(UClass* SpawningType,  float SpawnHeight, float Radius)
{
	if(SpawningType == nullptr){
		return;
	}
	if(Wizard == nullptr){
		return;
	}
	if(World)
	{
		FVector PlayerLocation = Wizard->GetActorLocation();
		FRotator Rotation = FRotator::ZeroRotator;
		FVector Location = PlayerLocation;
		float angle = FMath::RandRange(0.f, 2*PI);
		Location.X += FMath::Sin(angle)*Radius;
		Location.Y += FMath::Cos(angle)*Radius;
		Location.Z = SpawnHeight;
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		World->SpawnActor(SpawningType, &Location, &Rotation, params);
	}
}

void ASpawner::SpawnInRingAroundWizard(UClass* SpawningType,  float SpawnHeight, float Radius1, float Radius2)
{
	if(SpawningType == nullptr){
		return;
	}
	if(Wizard == nullptr){
		return;
	}
	if(World)
	{
		FVector PlayerLocation = Wizard->GetActorLocation();
		FRotator Rotation = FRotator::ZeroRotator;
		FVector Location = PlayerLocation;
		float angle = FMath::RandRange(0.f, 2*PI);
		float radius = FMath::RandRange(Radius1, Radius2);
		Location.X += FMath::Sin(angle)*radius;
		Location.Y += FMath::Cos(angle)*radius;
		Location.Z = SpawnHeight;
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		World->SpawnActor(SpawningType, &Location, &Rotation, params);
	}
}


void ASpawner::SpawnInSquareAroundWizard(UClass* SpawningType,  float SpawnHeight, float Length)
{
	if(SpawningType == nullptr){
		return;
	}
	if(Wizard == nullptr){
		return;
	}
	if(World)
	{
		FVector PlayerLocation = Wizard->GetActorLocation();
		FRotator Rotation = FRotator::ZeroRotator;
		FVector Location = PlayerLocation;
		Location.X += FMath::RandRange(PlayerLocation.X-Length, PlayerLocation.X+Length);
		Location.Y += FMath::RandRange(PlayerLocation.Y-Length, PlayerLocation.Y+Length);
		Location.Z = SpawnHeight;
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		World->SpawnActor(SpawningType, &Location, &Rotation, params);
	}
}
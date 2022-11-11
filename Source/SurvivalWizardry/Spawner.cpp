// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Wizard.h"
#include "Engine/World.h"
#include "HealthPack.h"

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

void ASpawner::SpawnHealtHPack(TSubclassOf<class AHealthPack> HealthPackClass, float LocationZAxis2)
{
	if(HealthPackClass == nullptr){
		UE_LOG(LogTemp, Display, TEXT("NO ENEMY TYPE"));
		return;
	}
	if(Wizard == nullptr){
		UE_LOG(LogTemp, Display, TEXT("NO Wizard"));
		return;
	}
	if(World)
	{
		FVector Location;
		FRotator Rotation = FRotator::ZeroRotator;
		Location.X += FMath::RandRange(ArenaBottomLeftX, ArenaBottomLeftX + ArenaLengthX);
		Location.Y += FMath::RandRange(ArenaBottomLeftY, ArenaBottomLeftY + ArenaLengthY);
		Location.Z = LocationZAxis2;
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AHealthPack* pack = Cast<AHealthPack>(World->SpawnActor(HealthPackClass, &Location, &Rotation, params));
		if(pack) pack->wizard=Wizard;
	}
}

void ASpawner::SpawnEnemy(TSubclassOf<AEnemyBase> EnemyType,  float EnemyLocationZAxis2)
{
	if(EnemyType == nullptr){
		return;
	}
	if(Wizard == nullptr){
		return;
	}
	if(World)
	{
		FVector PlayerLocation = Wizard->GetActorLocation();
		FRotator Rotation = FRotator::ZeroRotator;

		FVector EnemyLocation = FVector::ZeroVector;
		EnemyLocation.Z = EnemyLocationZAxis2;
		if(GenerateLocation(EnemyLocation)==true){
			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AEnemyBase* enemy = Cast<AEnemyBase>(World->SpawnActor(EnemyType, &EnemyLocation, &Rotation, params));
			if(enemy) enemy->wizard=Wizard;
		}
	}
}

void ASpawner::SpawnMultipleEnemies(int NumberOfEnemies, TSubclassOf<AEnemyBase> EnemyType,  float EnemyLocationZAxis2)
{
	if(EnemyType == nullptr){
		return;
	}
	if(Wizard == nullptr){
		return;
	}
	if(World)
	{
		FVector PlayerLocation = Wizard->GetActorLocation();
		for(int i = 0; i<NumberOfEnemies; ++i)
		{
			SpawnEnemy(EnemyType, EnemyLocationZAxis2);
		}
	}
}

void ASpawner::SpawnHorde(int NumberOfEnemies, TSubclassOf<AEnemyBase> EnemyType,  float EnemyLocationZAxis2)
{
	if(EnemyType == nullptr){
		return;
	}
	if(Wizard == nullptr){
		return;
	}
	if(World)
	{
		FVector PlayerLocation = Wizard->GetActorLocation();
		FRotator Rotation = FRotator::ZeroRotator;

		FVector EnemyLocation = FVector::ZeroVector;
		EnemyLocation.Z = EnemyLocationZAxis2;
		if(GenerateLocation(EnemyLocation)==true){
			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			for(int i = 0; i<NumberOfEnemies; ++i)
			{
				AEnemyBase* enemy = Cast<AEnemyBase>(World->SpawnActor(EnemyType, &EnemyLocation, &Rotation, params));
				if(enemy) enemy->wizard=Wizard;
				EnemyLocation.X += FMath::RandRange(-100,100);
				EnemyLocation.Y += FMath::RandRange(-100,100);
			}
		}	
	}
}

bool ASpawner::GenerateLocation(FVector& Location)
{
	FVector PlayerLocation = Wizard->GetActorLocation();
	int32 quadrant = FMath::RandRange(0,3);
	float FirstArgX=0.f;
	float SecondArgX=0.f;
	float FirstArgY=0.f;
	float SecondArgY=0.f;
	switch(quadrant){
		case 0: FirstArgX = FMath::Max(ArenaBottomLeftX, PlayerLocation.X-AllowedDistanceFromPlayerXBottom);
				SecondArgX = PlayerLocation.X-ForbiddenDistanceFromPlayerXBottom;
				FirstArgY = FMath::Max(ArenaBottomLeftY, PlayerLocation.Y-AllowedDistanceFromPlayerYLeft);
				SecondArgY = FMath::Min(PlayerLocation.Y+AllowedDistanceFromPlayerYRight, ArenaBottomLeftY+ArenaLengthY);
				break;
		case 1: FirstArgX = PlayerLocation.X+ForbiddenDistanceFromPlayerXTop;
				SecondArgX = FMath::Min(PlayerLocation.X+AllowedDistanceFromPlayerXTop, ArenaBottomLeftX + ArenaLengthX);
				FirstArgY = FMath::Max(ArenaBottomLeftY, PlayerLocation.Y-AllowedDistanceFromPlayerYLeft);
				SecondArgY = FMath::Min(PlayerLocation.Y+AllowedDistanceFromPlayerYRight, ArenaBottomLeftY+ArenaLengthY);
				break;
		case 2: FirstArgX = FMath::Max(ArenaBottomLeftX, PlayerLocation.X-AllowedDistanceFromPlayerXBottom);
				SecondArgX = FMath::Min(PlayerLocation.X+AllowedDistanceFromPlayerXTop, ArenaBottomLeftX+ArenaLengthX);
				FirstArgY = FMath::Max(ArenaBottomLeftY, PlayerLocation.Y-AllowedDistanceFromPlayerYLeft);
				SecondArgY = PlayerLocation.Y-ForbiddenDistanceFromPlayerYLeft;
				break;
		case 3: FirstArgX = FMath::Max(ArenaBottomLeftX, PlayerLocation.X-AllowedDistanceFromPlayerXBottom);
				SecondArgX = FMath::Min(PlayerLocation.X+AllowedDistanceFromPlayerXTop, ArenaBottomLeftX+ArenaLengthX);
				FirstArgY = PlayerLocation.Y+ForbiddenDistanceFromPlayerYRight;
				SecondArgY = FMath::Min(PlayerLocation.Y+AllowedDistanceFromPlayerYRight, ArenaBottomLeftY + ArenaLengthY);
				break;
	}

	if(FirstArgX>SecondArgX || FirstArgY>SecondArgY)
	{
		quadrant= (quadrant+1)%3;
		switch(quadrant){
		case 0: FirstArgX = FMath::Max(ArenaBottomLeftX, PlayerLocation.X-AllowedDistanceFromPlayerXBottom);
				SecondArgX = PlayerLocation.X-ForbiddenDistanceFromPlayerXBottom;
				FirstArgY = FMath::Max(ArenaBottomLeftY, PlayerLocation.Y-AllowedDistanceFromPlayerYLeft);
				SecondArgY = FMath::Min(PlayerLocation.Y+AllowedDistanceFromPlayerYRight, ArenaBottomLeftY+ArenaLengthY);
				break;
		case 1: FirstArgX = PlayerLocation.X+ForbiddenDistanceFromPlayerXTop;
				SecondArgX = FMath::Min(PlayerLocation.X+AllowedDistanceFromPlayerXTop, ArenaBottomLeftX + ArenaLengthX);
				FirstArgY = FMath::Max(ArenaBottomLeftY, PlayerLocation.Y-AllowedDistanceFromPlayerYLeft);
				SecondArgY = FMath::Min(PlayerLocation.Y+AllowedDistanceFromPlayerYRight, ArenaBottomLeftY+ArenaLengthY);
				break;
		case 2: FirstArgX = FMath::Max(ArenaBottomLeftX, PlayerLocation.X-AllowedDistanceFromPlayerXBottom);
				SecondArgX = FMath::Min(PlayerLocation.X+AllowedDistanceFromPlayerXTop, ArenaBottomLeftX+ArenaLengthX);
				FirstArgY = FMath::Max(ArenaBottomLeftY, PlayerLocation.Y-AllowedDistanceFromPlayerYLeft);
				SecondArgY = PlayerLocation.Y-ForbiddenDistanceFromPlayerYLeft;
				break;
		case 3: FirstArgX = FMath::Max(ArenaBottomLeftX, PlayerLocation.X-AllowedDistanceFromPlayerXBottom);
				SecondArgX = FMath::Min(PlayerLocation.X+AllowedDistanceFromPlayerXTop, ArenaBottomLeftX+ArenaLengthX);
				FirstArgY = PlayerLocation.Y+ForbiddenDistanceFromPlayerYRight;
				SecondArgY = FMath::Min(PlayerLocation.Y+AllowedDistanceFromPlayerYRight, ArenaBottomLeftY + ArenaLengthY);
				break;
		}
	}

	if(FirstArgX>SecondArgX || FirstArgY>SecondArgY)
	{
		UE_LOG(LogTemp, Display, TEXT("false"));
		return false;
	}
	Location.X=FMath::RandRange(FirstArgX, SecondArgX);
	Location.Y=FMath::RandRange(FirstArgY, SecondArgY);
	return true;

}
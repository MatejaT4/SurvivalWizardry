// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class SURVIVALWIZARDRY_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawner();

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ArenaBottomLeftX = -3900.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ArenaBottomLeftY = 4750.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ArenaLengthX = 8750.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ArenaLengthY = 9700.f;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class AWizard* Wizard;

	UFUNCTION(BlueprintCallable, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	void SpawnOnCircleAroundWizard(UClass* SpawningType,  float SpawnHeight, float Radius);

	UFUNCTION(BlueprintCallable, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	void SpawnInSquareAroundWizard(UClass* SpawningType,  float SpawnHeight, float Length);

	UFUNCTION(BlueprintCallable, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	void SpawnInRingAroundWizard(UClass* SpawningType,  float SpawnHeight, float Radius1, float Radius2);

	UFUNCTION(BlueprintCallable, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	void SpawnInArena(UClass* SpawningType,  float SpawnHeight);

	UPROPERTY()
	UWorld* World;

};

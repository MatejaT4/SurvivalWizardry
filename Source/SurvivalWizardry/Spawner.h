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
	float EnemyTimer = 1.f;
	
	// UPROPERTY(EditAnywhere, Category = "Spawn")
	// float MinRangeX = 200.f;
	// UPROPERTY(EditAnywhere, Category = "Spawn")
	// float MaxRangeX = 1000.f;
	// UPROPERTY(EditAnywhere, Category = "Spawn")
	// float MinRangeY = 500.f;
	// UPROPERTY(EditAnywhere, Category = "Spawn")
	// float MaxRangeY = 1000.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float EnemyLocationZAxis = 90.f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ArenaBottomLeftX = -3900.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ArenaBottomLeftY = 4750.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ArenaLengthX = 8750.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ArenaLengthY = 9700.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ForbiddenDistanceFromPlayerXBottom = 500.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ForbiddenDistanceFromPlayerXTop = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ForbiddenDistanceFromPlayerYLeft = 1000.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ForbiddenDistanceFromPlayerYRight = 1000.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AllowedDistanceFromPlayerXBottom = 3000.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AllowedDistanceFromPlayerXTop = 3000.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AllowedDistanceFromPlayerYLeft = 3000.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AllowedDistanceFromPlayerYRight = 3000.f;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class AWizard* Wizard;

	UFUNCTION(BlueprintCallable, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	void SpawnHealtHPack(TSubclassOf<class AHealthPack> HealthPackClass, float LocationZAxis2);

	UFUNCTION(BlueprintCallable, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	void SpawnEnemy(TSubclassOf<class AEnemyBase> EnemyType, float EnemyLocationZAxis2);

	UFUNCTION(BlueprintCallable, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	void SpawnMultipleEnemies(int NumberOfEnemies, TSubclassOf<class AEnemyBase> EnemyType,  float EnemyLocationZAxis2);

	UFUNCTION(BlueprintCallable, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	void SpawnHorde(int NumberOfEnemies, TSubclassOf<class AEnemyBase> EnemyType,  float EnemyLocationZAxis2);

	FTimerHandle EnemyTimerHandle;

	UPROPERTY()
	UWorld* World;

	bool GenerateLocation(FVector& Location);

};

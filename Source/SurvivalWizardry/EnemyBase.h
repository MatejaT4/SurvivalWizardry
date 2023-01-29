// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"


UCLASS()
class SURVIVALWIZARDRY_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	AEnemyBase();

public:	
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	virtual void Move(float DeltaTime);

	UPROPERTY()
	class AWizard* wizard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience = 10.f;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Speed = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float TurnRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Damage = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth = 100.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "Custom Variables")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Custom Variables")
	class USoundBase* DeathSound;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComponent, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
};

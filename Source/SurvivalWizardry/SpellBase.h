// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellStructure.h"
#include "SpellBase.generated.h"

UCLASS()
class SURVIVALWIZARDRY_API ASpellBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpellBase();

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 100.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Size = 1.f;

	UPROPERTY(BlueprintReadWrite, Category = "Level", meta = (AllowPrivateAccess = "true"))
	int Lvl = 1;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float CooldownTime = 2.f;

	void HandleDestruction();

	void StartCasting();

	void StopCasting();

	void PauseCasting();

	void UnpauseCasting();
	
	void LevelUp();
	
	void Initialize(FSpellStructure* Row);
protected:
	virtual void BeginPlay() override;
	
	virtual void CastProjectile();	

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileLocationZAxis = 20.f;

	UPROPERTY()
	FTimerHandle CooldownTimerHandle;
	
	UPROPERTY()
	class AWizard* Wizard;
};

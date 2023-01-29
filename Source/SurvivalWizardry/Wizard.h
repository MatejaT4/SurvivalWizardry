// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wizard.generated.h"

UCLASS()
class SURVIVALWIZARDRY_API AWizard : public ACharacter
{
	GENERATED_BODY()

public:
	AWizard();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void HandleGameEnd(bool IsVictory);
	void HandleGameStart();
	void BecomeInvincible(float Duration);
	void StopBeingInvincible();
	bool CheckIfInvincible();
	bool Heal(float HealValue);

private:

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, Category = "Health")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AStaffBase> Staff;

	UPROPERTY(BlueprintReadWrite, Category = "Staff", meta = (AllowPrivateAccess = "true"))
	class AStaffBase* StaffInstance;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxHealth = 200.f;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsInvincible=false;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsDead=false;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsVictorious=false;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;
};

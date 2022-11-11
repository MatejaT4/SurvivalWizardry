// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaffBase.generated.h"

UCLASS()
class SURVIVALWIZARDRY_API AStaffBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AStaffBase();

	void HandleDestruction();
	void StartCasting();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff", meta = (AllowPrivateAccess = "true"))
	int32 numSlots = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff", meta = (AllowPrivateAccess = "true"))
	TArray< FName > spellsNames;
	
	UPROPERTY()
	TArray< class ASpellBase* > spells;

	UFUNCTION(BlueprintCallable, Category = "Spell", meta = (AllowPrivateAccess = "true"))
	bool AddSpell(FName name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* Table;

	UFUNCTION(BlueprintCallable, Category = "Spell", meta = (AllowPrivateAccess = "true"))
	int CheckIfExistsAndReturnLevel(FName name);

};

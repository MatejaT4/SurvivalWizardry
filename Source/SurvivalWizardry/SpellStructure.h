// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "SpellStructure.generated.h"
USTRUCT(BlueprintType)
struct FSpellStructure : public FTableRowBase
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	FName SpellName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	TSubclassOf<class ASpellBase> SpellClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	class UTexture2D* DisplayTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float Size;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SpellBase.h"
#include "HomingProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALWIZARDRY_API AHomingProjectileSpell : public ASpellBase
{
	GENERATED_BODY()
	void CastProjectile() override;
};

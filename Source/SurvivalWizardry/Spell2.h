// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBase.h"
#include "Spell2.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALWIZARDRY_API ASpell2 : public ASpellBase
{
	GENERATED_BODY()
	void CastProjectile() override;
};

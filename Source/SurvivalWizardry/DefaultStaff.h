// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaffBase.h"
#include "DefaultStaff.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALWIZARDRY_API ADefaultStaff : public AStaffBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

};

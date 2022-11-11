// Fill out your copyright notice in the Description page of Project Settings.


#include "StaffBase.h"
#include "SpellBase.h"
#include "Engine/DataTable.h"
#include "SpellStructure.h"
#include "UObject/NameTypes.h"

AStaffBase::AStaffBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh")); 
	RootComponent = BaseMesh;
}

void AStaffBase::BeginPlay()
{
	Super::BeginPlay();

	spells.SetNum(numSlots);
	spellsNames.SetNum(numSlots);	
	AddSpell(FName(TEXT("FireBall"))); //Add first spell

}

void AStaffBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStaffBase::StartCasting()
{
	for(int i=0; i<numSlots; ++i)
	{
		if(spells[i] != nullptr)
			spells[i]->StartCasting();
	}
}

void AStaffBase::HandleDestruction()
{
	for(int i=0; i<numSlots; ++i)
	{
		if(spells[i] != nullptr)
			spells[i]->HandleDestruction();
	}
	Destroy();
}

bool AStaffBase::AddSpell(FName name)
{
	//If spell already exists, level it up
	for(int i = 0; i < numSlots; ++i)
	{
		if(spellsNames[i].IsEqual(name) && spells[i])
		{
			spells[i]->PauseCasting();
			spells[i]->Lvl=spells[i]->Lvl+1;
			spells[i]->InitializeParameters();
			spells[i]->UnpauseCasting();
			return true;
		}
	}
	//If it doesnt exist, check if there is free slot and add it if there is
	for(int i = 0; i < numSlots; ++i)
	{
		if(spellsNames[i].IsNone() == true)
		{
			if(Table) 
			{
			    const FString ContextString(TEXT("context"));
			    FSpellStructure* Row = Table->FindRow<FSpellStructure>(name, ContextString ,true);
			    if(Row) 
				{
					FVector Location = FVector();
					FRotator Rotation = FRotator();
					spells[i] = Cast<ASpellBase>(GetWorld()->SpawnActor(Row->SpellClass, &Location, &Rotation));
					if(spells[i])
					{
						spells[i]->ProjectileClass = Row->ProjectileClass;
						spells[i]->Damage = Row->Damage;
						spells[i]->CooldownTime = Row->Cooldown;
						spells[i]->StartCasting();
						spellsNames[i] = name;
						return true;
					}
				}
			}
		}
	}
	return false;
}

int AStaffBase::CheckIfExistsAndReturnLevel(FName name)
{
	for(int i = 0; i < numSlots; ++i)
	{
		if(spellsNames[i].IsEqual(name) && spells[i])
		{
			return spells[i]->Lvl;
		}
	}
	return -1;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivalWizardryGameModeBase.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	SurvivalWizardryGameModeBase = Cast<ASurvivalWizardryGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if(Damage <= 0.f) return;
	Health -= Damage;
	if(Health <= 0.f && SurvivalWizardryGameModeBase)
	{
		SurvivalWizardryGameModeBase->ActorDied(DamagedActor);
	}
}

bool UHealthComponent::Heal(float HealValue)
{
	if(Health < MaxHealth)
	{
		Health = FMath::Clamp(Health + HealValue, 0.f, MaxHealth);
		return true;
	}
	return false;
}

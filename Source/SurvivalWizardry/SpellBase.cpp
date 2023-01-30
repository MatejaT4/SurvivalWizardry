// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"
#include "Engine/World.h"
#include "ProjectileBase.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Wizard.h"
#include "SpellStructure.h"

ASpellBase::ASpellBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpellBase::BeginPlay()
{
	Super::BeginPlay();
	Wizard = Cast<AWizard>(UGameplayStatics::GetPlayerPawn(this,0));
}

void ASpellBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpellBase::StartCasting()
{
	GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &ASpellBase::CastProjectile, CooldownTime, true);	
}

void ASpellBase::StopCasting()
{
	GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
}

void ASpellBase::PauseCasting()
{
	GetWorldTimerManager().PauseTimer(CooldownTimerHandle);
}

void ASpellBase::UnpauseCasting()
{
	GetWorldTimerManager().UnPauseTimer(CooldownTimerHandle);
}

void ASpellBase::LevelUp()
{
	++Lvl;
	if(Lvl % 2 == 0) Damage = Damage * 1.5;
	else CooldownTime = CooldownTime * 0.8; 
}

void ASpellBase::Initialize(FSpellStructure* Row)
{
	ProjectileClass = Row->ProjectileClass;
	Damage = Row->Damage;
	CooldownTime = Row->Cooldown;
	Size = Row->Size;
}

void ASpellBase::CastProjectile()
{
	FVector Location = Wizard->GetActorLocation();
	Location.Z = ProjectileLocationZAxis;
	FRotator Rotation = Wizard->GetActorRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation) ;
	if(Projectile) 
	{
		Projectile->SetOwner(this);
		Projectile->Initialize(Damage, Size, 10);
	}
}

void ASpellBase::HandleDestruction()
{
	GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
	Destroy();
}

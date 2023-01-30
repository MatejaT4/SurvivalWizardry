// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingProjectileSpell.h"
#include "Engine/World.h"
#include "../ProjectileBase.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "../Wizard.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Components/BoxComponent.h"
#include "../EnemyBase.h"

void AHomingProjectileSpell::CastProjectile()
{
	FVector Location = Wizard->GetActorLocation();
	Location.Z = ProjectileLocationZAxis;
	FRotator Rotation = Wizard->GetActorRotation();

    Rotation.Yaw+=60;
    auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation) ;
    if(Projectile) 
    {
        Projectile->SetOwner(this);
		Projectile->IsHoming=true;
        Projectile->Initialize(Damage, Size, 0);
    }   
}
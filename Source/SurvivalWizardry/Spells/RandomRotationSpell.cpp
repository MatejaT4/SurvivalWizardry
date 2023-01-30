// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomRotationSpell.h"
#include "Engine/World.h"
#include "../ProjectileBase.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "../Wizard.h"

void ARandomRotationSpell::CastProjectile()
{
	FVector Location = Wizard->GetActorLocation();
	Location.Z = ProjectileLocationZAxis;
	float yaw = FMath::FRandRange(-180.f, 180.f);
	FRotator Rotation = FRotator(0.f, yaw, 0.f);
    Rotation.Yaw+=60;
    auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation) ;
    if(Projectile) 
    {
        Projectile->SetOwner(this);
        Projectile->Initialize(Damage, Size, 10);
    }  
}
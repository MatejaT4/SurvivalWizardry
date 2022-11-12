// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialProjectileSpell.h"
#include "Engine/World.h"
#include "../ProjectileBase.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "../Wizard.h"

void ARadialProjectileSpell::CastProjectile()
{
	FVector Location = Wizard->GetActorLocation();
	Location.Z = ProjectileLocationZAxis;
	FRotator Rotation = Wizard->GetActorRotation();

    for(int i=0; i<6; ++i)
    {
        Rotation.Yaw+=60;
        auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation) ;
        if(Projectile) 
        {
            Projectile->SetOwner(this);
            Projectile->Damage=Damage;
        }  
    }
}
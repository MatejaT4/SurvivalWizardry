// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/BoxComponent.h"
#include "EnemyBase.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement")); 
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlap);
}

void AProjectileBase::Initialize(float damage, float size, int numberOfPierces)
{
	if(IsHoming)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundActors);
		float Distance;
		AEnemyBase* Target = Cast<AEnemyBase>(UGameplayStatics::FindNearestActor(GetActorLocation(), FoundActors, Distance));
		if(Target){
			ProjectileMovement->HomingTargetComponent = Target->GetCollision();
			ProjectileMovement->bIsHomingProjectile = true;
			ProjectileMovement->HomingAccelerationMagnitude = 5000.f;
		}
		
	}
	ProjectileMovement->InitialSpeed=Speed;
	ProjectileMovement->MaxSpeed=Speed;
	Damage=damage;
	Size=size;
	NumberOfPierces=numberOfPierces;
	CollisionMesh->SetWorldScale3D(FVector(Size, Size, Size));

}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	auto DamageTypeClass = UDamageType::StaticClass();
	if(OtherActor && OtherActor != this)
	{
		if(Cast<AEnemyBase>(OtherActor)){
			UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, DamageTypeClass);
			--NumberOfPierces;
			if(NumberOfPierces < 0)
			{
				Destroy();
			}
		}	
		else
		{
			Destroy();
		}	
	}
}

class UProjectileMovementComponent* AProjectileBase::GetProjectileMovement()
{
	return ProjectileMovement;
}




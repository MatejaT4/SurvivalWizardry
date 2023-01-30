// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Wizard.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);

	CollisionMesh->SetGenerateOverlapEvents(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	wizard = Cast<AWizard>(UGameplayStatics::GetPlayerPawn(this,0));
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlap);
	HealthComponent->MaxHealth = MaxHealth;
	HealthComponent->Health = MaxHealth;
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//move enemy towards wizard
	Move(DeltaTime);		
}

void AEnemyBase::Move(float DeltaTime)
{
	FVector enemyLocation = GetActorLocation();
	if(wizard)
	{
		FVector wizardLocation = wizard->GetActorLocation();
		FRotator current = GetActorRotation();
		FVector direction = wizardLocation - enemyLocation;
		direction.Normalize();
		FRotator target = direction.Rotation();
		FRotator interpolation = FMath::RInterpTo(current, target, DeltaTime, TurnRate);	
		interpolation.Pitch=0.f;
		interpolation.Roll=0.f;
		SetActorRotation(interpolation);
		enemyLocation.X += interpolation.Vector().X * DeltaTime * Speed;
		enemyLocation.Y += interpolation.Vector().Y * DeltaTime * Speed;
		SetActorLocation(enemyLocation);
	}
}

void AEnemyBase::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if(Cast<AWizard>(OtherActor) == wizard)
	{	
		if(wizard && wizard->CheckIfInvincible() == false)
		{
			wizard->BecomeInvincible(1.f);
			UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, UDamageType::StaticClass());
		}
	}
}

void AEnemyBase::HandleDestruction() 
{
    Destroy();
	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}	
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
}

UBoxComponent* AEnemyBase::GetCollision()
{
	return CollisionMesh;
}
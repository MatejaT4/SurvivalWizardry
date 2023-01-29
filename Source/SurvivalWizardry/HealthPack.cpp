// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Wizard.h"
#include "HealthComponent.h"

AHealthPack::AHealthPack()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
}

void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	wizard = Cast<AWizard>(UGameplayStatics::GetPlayerPawn(this,0));
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlap);
}

void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealthPack::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if(Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(),0))
	{	
		if(wizard && wizard->Heal(HealValue)) Destroy();
	}
}

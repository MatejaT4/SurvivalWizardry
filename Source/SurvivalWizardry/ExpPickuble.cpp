// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpPickuble.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Wizard.h"
#include "SurvivalWizardryGameModeBase.h"

AExpPickuble::AExpPickuble()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
}

void AExpPickuble::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AExpPickuble::OnOverlap);
}

void AExpPickuble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExpPickuble::OnOverlap(
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
		Cast<ASurvivalWizardryGameModeBase>(UGameplayStatics::GetGameMode(this))->AddExperience(Exp);
		Destroy();
	}
}

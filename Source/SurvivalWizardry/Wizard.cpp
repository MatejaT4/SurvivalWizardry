// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "StaffBase.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AWizard::AWizard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Disable Character rotation with camera
	bUseControllerRotationYaw = false;

	//MOVEMENT COMPONENT SETUP
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->bConstrainToPlane = true; 
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//SPRING ARM SETUP
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true); // Don't rotate with character
	SpringArm->bDoCollisionTest = false; // Don't pull camera when collision happens

	//CAMERA SETUM
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//HEALTH COMPONENT
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void AWizard::BeginPlay()
{
	Super::BeginPlay();
	//initialize stats
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	HealthComponent->MaxHealth = MaxHealth;
	HealthComponent->Health = MaxHealth;
	//Fatching staff
	StaffInstance = GetWorld()->SpawnActor<AStaffBase>(Staff, GetActorLocation(), FRotator::ZeroRotator);
	if(StaffInstance) StaffInstance->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("WeaponSocket"));
}

void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWizard::HandleGameEnd(bool IsVictory)
{
	if(IsVictory==false) IsDead=true;
	else IsVictorious=true;

	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	if(StaffInstance) StaffInstance->HandleDestruction();
}

void AWizard::HandleGameStart() 
{
	StaffInstance->StartCasting();
}

void AWizard::BecomeInvincible(float Duration)
{
	IsInvincible=true;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWizard::StopBeingInvincible, Duration, false);	
}

void AWizard::StopBeingInvincible()
{
	IsInvincible=false;
}

bool AWizard::CheckIfInvincible()
{
	return IsInvincible;
}

float AWizard::GetHealthPercent() const
{
	return HealthComponent->Health / HealthComponent->MaxHealth;
}

bool AWizard::Heal(float HealValue)
{
	return HealthComponent->Heal(HealValue);
}

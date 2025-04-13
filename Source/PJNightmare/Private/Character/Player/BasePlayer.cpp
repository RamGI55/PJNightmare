// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/BasePlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/PlayerSkillComponent.h"
#include "Components/PlayerStatComponets.h"
#include "DataWrappers/ChaosVDQueryDataWrappers.h"


// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowingCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraBoom->bUsePawnControlRotation = false;
	
	// input 
#pragma region Input
	
#pragma endregion

	StatComponent = CreateDefaultSubobject<UPlayerStatComponets>(TEXT("StatComponent"));
	SkillComponent = CreateDefaultSubobject<UPlayerSkillComponent>(TEXT("SkillComponent"));
	
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

#pragma region Movements
void ABasePlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);
		const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FowardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABasePlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

#pragma region RPC

void ABasePlayer::Server_Sprint_Implementation()
{
	Multi_Sprint(); 
}

void ABasePlayer::Multi_Sprint_Implementation()
{
	// Sprint function
	if (Controller != nullptr)
	{
		StatComponent->SetSpeed(1250.f); // ?? 
		GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetSpeed();  
	}
}

void ABasePlayer::ServerAiming_Implementation()
{
}

void ABasePlayer::Multi_Aiming_Implementation()
{
}

void ABasePlayer::Server_StopAiming_Implementation()
{
}

void ABasePlayer::Multi_StopAiming_Implementation()
{
}

void ABasePlayer::Server_Fire_Implementation()
{
}

void ABasePlayer::Multi_Fire_Implementation()
{
}

#pragma endregion 
void ABasePlayer::Server_Dash_Implementation()
{
	Multi_Dash();
}

void ABasePlayer::Multi_Dash_Implementation()
{
	if (Controller != nullptr)
	{
		// Dash Logic here
	}
}


#pragma endregion




// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	StatComponent->Basicintialiser(); 
}



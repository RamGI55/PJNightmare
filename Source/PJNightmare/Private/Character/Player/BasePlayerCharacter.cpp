// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/BasePlayerCharacter.h"
#include "Debughelper.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABasePlayerCharacter::ABasePlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom -> SetupAttachment(GetRootComponent());
	CameraBoom -> TargetArmLength = 300.f;
	CameraBoom -> SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom -> bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera -> SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	Camera ->  bUsePawnControlRotation = false;

	GetCharacterMovement() ->RotationRate = FRotator (0.f, 500.f ,0.f);
	GetCharacterMovement() ->MaxWalkSpeed = 600.f;
	GetCharacterMovement() ->bOrientRotationToMovement = true;
	GetCharacterMovement() ->BrakingDecelerationWalking = 2000.f;

	
} 

void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Debug::Print(TEXT("ABasePlayerCharacter::BeginPlay"));
	
}

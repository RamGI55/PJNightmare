// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/BasePlayerCharacter.h"
#include "Debughelper.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Misc/PJNMTags.h"

#include "Components/EnhancedInputBaseComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BaseAbilitySystem.h"

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

void ABasePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent && AbilityAttributeSet)
	{
		const FString ASCText = FString::Printf(TEXT("Onwer Actor : %s, AvatarActor : %s" ), *AbilitySystemComponent->GetOwner()->GetName(), *AbilitySystemComponent->GetAvatarActor()->GetName());
		Debug::Print (TEXT("Ability System Component Vaild : ") + ASCText, FColor::Green);

		Debug::Print (TEXT("AttributeSet Component Vaild : ") + ASCText,FColor::Purple); 
	}

	
}

void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to Assign a Vaild data asset"))
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);  

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext,0);

	UEnhancedInputBaseComponent* BaseInputComponent = CastChecked<UEnhancedInputBaseComponent>(PlayerInputComponent); 

	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, PJNMGamplayTags::InputTag_Move, ETriggerEvent::Triggered,this, &ThisClass::Input_Move);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, PJNMGamplayTags::InputTag_Look, ETriggerEvent::Triggered,this, &ThisClass::Input_Look); 

}
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Debug::Print(TEXT("ABasePlayerCharacter::BeginPlay"));
	
}

void ABasePlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput (RightDirection, MovementVector.X);
	}
}

void ABasePlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

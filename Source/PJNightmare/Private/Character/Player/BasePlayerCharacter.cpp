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
#include "VrmAnimInstance.h"

#include "AbilitySystem/BaseAbilitySystem.h"
#include "Components/AttackComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/BaseWeapon.h"


#include "Widget/WOverHead.h"

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

	GetCharacterMovement()->RotationRate = FRotator (0.f, 500.f ,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>("OverheadWidget");
	OverheadWidget -> SetupAttachment(GetRootComponent());

	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	AttackComponent->SetIsReplicated(true);

	// In constructor:
	bReplicates = true;
	bAlwaysRelevant = true;
	SetReplicatingMovement(true);

	// Ensure consistent transform updates
	GetRootComponent()->SetMobility(EComponentMobility::Movable);
}

void ABasePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent && AbilityAttributeSet)
	{
		
	}
}

void ABasePlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Register the overlapping weapon

	DOREPLIFETIME_CONDITION(ABasePlayerCharacter, OverlappedWeapon, COND_OwnerOnly);
	DOREPLIFETIME(ABasePlayerCharacter, isRuninServer); 
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
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, PJNMGamplayTags::InputTag_Sprint, ETriggerEvent::Triggered,this, &ThisClass::Input_Run);
	BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, PJNMGamplayTags::InputTag_Attack, ETriggerEvent::Triggered,this, &ThisClass::Input_Attack); 
}
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Debug each part separately
	Debug::Print(FString::Printf(TEXT("HasAuthority: %s"), 
		HasAuthority() ? TEXT("TRUE") : TEXT("FALSE")), FColor::White);
    
	if (!HasAuthority())
	{
		Debug::Print("Authority check passed - this is a client", FColor::Yellow);
        
		USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
		if (SkeletalMeshComp)
		{
			Debug::Print("Mesh exists", FColor::Green);
            
			UAnimInstance* AnimInst = SkeletalMeshComp->GetAnimInstance();
			if (AnimInst)
			{
				Debug::Print(FString::Printf(TEXT("AnimInstance class: %s"), 
					*AnimInst->GetClass()->GetName()), FColor::Blue);
                
				UVrmAnimInstance* VrmAnim = Cast<UVrmAnimInstance>(AnimInst);
				if (VrmAnim)
				{
					Debug::Print("VRM AnimInstance found!", FColor::Green);
					VrmAnim->MetaObject = nullptr;
					Debug::Print("VRM Disabled on Client", FColor::Red);
				}
				else
				{
					Debug::Print("VRM AnimInstance cast FAILED", FColor::Red);
				}
			}
			else
			{
				Debug::Print("No AnimInstance found", FColor::Red);
			}
		}
		else
		{
			Debug::Print("No Mesh found", FColor::Red);
		}
	}
	else
	{
		Debug::Print("This is SERVER - VRM should run normally", FColor::Green);
	}

}

void ABasePlayerCharacter::OnRep_OverlappingWeapon(ABaseWeapon* LastWeapon)
{
	if (IsLocallyControlled())
	{
		if (OverlappedWeapon)
		{
			OverlappedWeapon->ShowPickupWidget(true); 
		}
		if (LastWeapon)
		{
			LastWeapon->ShowPickupWidget(false); 
		}
	}
}

void ABasePlayerCharacter::SetOverlappingWeapon(ABaseWeapon* Weapon)
{
	if (OverlappedWeapon)
	{
		OverlappedWeapon->ShowPickupWidget(false); 
	}
	OverlappedWeapon = Weapon;
	if (IsLocallyControlled())
	{
		if (OverlappedWeapon)
		{
			OverlappedWeapon->ShowPickupWidget(true); 
		}
	}
}

#pragma region Inputs 
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

void ABasePlayerCharacter::Input_Run(const FInputActionValue& InputActionValue)
{
	if (InputActionValue.Get<bool>())
	{
		GetCharacterMovement()->MaxWalkSpeed = 1200.f;
		if (!HasAuthority())
		{
			GetCharacterMovement()->MaxWalkSpeed = 1200.f;
		}
		
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	} 
}

void ABasePlayerCharacter::Input_Attack(const FInputActionValue& InputActionValue)
{
	// logic for the attack input 
}
#pragma endregion

void ABasePlayerCharacter::tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	if (!HasAuthority())
	{
		FRotator CharRot = GetActorRotation();
		FRotator ControlRot = GetControlRotation();
        
		Debug::Print(FString::Printf(TEXT("Char Yaw: %.2f | Control Yaw: %.2f"), 
			CharRot.Yaw, ControlRot.Yaw), FColor::Cyan);
	}
}
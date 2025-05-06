// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/PlayerSkillComponent.h"
#include "Components/PlayerStatComponets.h"
#include "DataWrappers/ChaosVDQueryDataWrappers.h"
#include "Components/SkeletalMeshComponent.h"
#include "InputMappingContext.h"
#include "PlayerController/IngamePlayerController.h"


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
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.f, 0.0f); 

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	GetCharacterMovement()->MaxWalkSpeed =600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowingCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	CameraBoom->bUsePawnControlRotation = false;
	
	StatComponent = CreateDefaultSubobject<UPlayerStatComponets>(TEXT("PlayerStatComponent"));
	SkillComponent = CreateDefaultSubobject<UPlayerSkillComponent>(TEXT("PlayerSkillComponent"));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMesh(TEXT("'/Game/Characters/Mannequins/Meshes/SKM_Quinn'"));
	if (PlayerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	}

	StatComponent->Basicintialiser();
	// input
	
#pragma region Input
	
}
#pragma endregion



void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
{
	if (AIngamePlayerController* PlayerController = Cast<AIngamePlayerController>(GetController()))
	{
		 if (PlayerController->MovingAction)
		 {
			 EnhancedInput->BindAction(PlayerController->MovingAction, ETriggerEvent::Triggered, this, &ABasePlayer::Move); 
		 }
		if (PlayerController->LookingAction)
		{
			EnhancedInput->BindAction(PlayerController->LookingAction, ETriggerEvent::Triggered, this, &ABasePlayer::Look);
		}
		if (PlayerController->RunningAction)
		{
			EnhancedInput->BindAction(PlayerController->RunningAction, ETriggerEvent::Triggered, this, &ABasePlayer::Server_Sprint); 
		}
	}
}
	
}

#pragma region Movements
void ABasePlayer::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);
	if (!FMath::IsNearlyZero(MovementVector.X))
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.X);
	}
	if (!FMath::IsNearlyZero(MovementVector.Y))
	{
		AddMovementInput(GetActorRightVector(), MovementVector.Y);
		
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
	if (StatComponent != nullptr)
	{
		StatComponent->SetSpeed(1250.f); // should make it as the variables. 
		GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetSpeed();  
	}
}

void ABasePlayer::Server_StopSprint_Implementation()
{
	Multi_StopSprint();
}

void ABasePlayer::Multi_StopSprint_Implementation()
{
	if (StatComponent != nullptr)
	{
		StatComponent->SetSpeed(600.f);
		GetCharacterMovement()-> MaxWalkSpeed = StatComponent->GetSpeed();
	}
}
// This Aiming system must move to the shooting or other components. 
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
	if (!IsLocallyControlled())
	{
		return; 
	}
	
	Super::BeginPlay();
	StatComponent->Basicintialiser();
	/*FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABasePlayer::SetEnhancedInput, .3f, false);*/
	DebugMovementStatus();
	
}

void ABasePlayer::DebugMovementStatus()
{
	UE_LOG(LogTemp, Warning, TEXT("--- Character Movement Debug Info ---"));
	UE_LOG(LogTemp, Warning, TEXT("Character: %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Network Role: %d"), GetLocalRole());
	UE_LOG(LogTemp, Warning, TEXT("Is Locally Controlled: %s"), IsLocallyControlled() ? TEXT("Yes") : TEXT("No"));
	UE_LOG(LogTemp, Warning, TEXT("Controller: %s"), GetController() ? *GetController()->GetName() : TEXT("None"));
	UE_LOG(LogTemp, Warning, TEXT("Enhanced Input Component Valid: %s"), EnhancedInputComponent ? TEXT("Yes") : TEXT("No"));
	UE_LOG(LogTemp, Warning, TEXT("Current Speed: %f"), GetVelocity().Size());
	UE_LOG(LogTemp, Warning, TEXT("Max Walk Speed: %f"), GetCharacterMovement()->MaxWalkSpeed);
	UE_LOG(LogTemp, Warning, TEXT("StatComponent Valid: %s"), StatComponent ? TEXT("Yes") : TEXT("No"));
	UE_LOG(LogTemp, Warning, TEXT("-----------------------------"));
}


void ABasePlayer::SetEnhancedInput()
{
	Super::SetupPlayerInputComponent(InputComponent);
    
	
}




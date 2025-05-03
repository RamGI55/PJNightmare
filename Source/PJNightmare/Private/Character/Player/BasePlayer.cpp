// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/BasePlayer.h"
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

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowingCamera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraBoom->bUsePawnControlRotation = false;
	
	StatComponent = CreateDefaultSubobject<UPlayerStatComponets>(TEXT("PlayerStatComponent"));
	SkillComponent = CreateDefaultSubobject<UPlayerSkillComponent>(TEXT("PlayerSkillComponent"));

	CameraBoom->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(CameraBoom);  
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	if (PlayerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	}

	StatComponent->Basicintialiser();

	PlayerController = Cast<AIngamePlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->GetMappings(); 
	}
	
	// input
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(this->InputComponent); 
#pragma region Input
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Move = (TEXT("'/Game/PJNightmare/Inputs/Actions/IA_Move'"));
	if (IA_Move.Object) MovementAction = IA_Move.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Zoom = (TEXT("'/Game/PJNightmare/Inputs/Actions/IA_Zoom'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Look = (TEXT("/'/Game/PJNightmare/Inputs/Actions/IA_Look'"));
	if (IA_Look.Object) LookingAction = IA_Look.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Dash = (TEXT("'/Game/PJNightmare/Inputs/Actions/IA_Dash'"));
	if (IA_Dash.Object) DashAction = IA_Dash.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Run = (TEXT("'/Game/PJNightmare/Inputs/Actions/IA_Run'"));
	if (IA_Run.Object) RunningAction = IA_Run.Object;
	
#pragma endregion
}


void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ABasePlayer::Move);
		EnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered, this, &ABasePlayer::Look);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered , this , &ABasePlayer::Server_Dash);	
		EnhancedInputComponent->BindAction(RunningAction, ETriggerEvent::Triggered, this, &ABasePlayer::Server_Sprint);
	}
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
	Super::BeginPlay();
	StatComponent->Basicintialiser(); 
}



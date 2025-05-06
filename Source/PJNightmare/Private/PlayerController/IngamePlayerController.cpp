// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/IngamePlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/Player/BasePlayer.h"


class UEnhancedInputLocalPlayerSubsystem;

AIngamePlayerController::AIngamePlayerController()
	:IC_DefaultContext(NULL),
	MovingAction(NULL),
	ZoomAction(NULL),
	DashAction(NULL),
	AttackAction(NULL),
	LookingAction(NULL),
	RunningAction(NULL)
{
	
}

void AIngamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem=
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (IC_DefaultContext)
			{
				Subsystem->AddMappingContext(IC_DefaultContext, 0); 
			}
		}
	}

}

void AIngamePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AIngamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
}

void AIngamePlayerController::SetupInputBinding()
{
	
}





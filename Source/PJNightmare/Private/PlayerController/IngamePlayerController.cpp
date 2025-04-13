// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/IngamePlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/Player/BasePlayer.h"


class UEnhancedInputLocalPlayerSubsystem;

AIngamePlayerController::AIngamePlayerController()
{

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMapping(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PJNightmare/Inputs/IMC_IngameNonAuto.IMC_IngameNonAuto'"));
	if (DefaultMapping.Succeeded())
	{
		IngameDefaultMapping = DefaultMapping.Object;
	}
}

void AIngamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	PossedPawn = Cast<ABasePlayer>(GetPawn());
}

void AIngamePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AIngamePlayerController::GetMappings()
{
	// PlayerController
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IngameDefaultMapping, 0);
	}
}





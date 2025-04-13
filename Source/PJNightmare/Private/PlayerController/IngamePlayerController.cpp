// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/IngamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "Character/Player/BasePlayer.h"


AIngamePlayerController::AIngamePlayerController()
{

	
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

/*void AIngamePlayerController::SetupInputComponent(class UIInputComponent* PlayerInputComponent)
{
	Super::SetupInputComponent();

	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Ongoing, this,&AIngamePlayerController::CallMove);
		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Ongoing, this,&AIngamePlayerController::CallMove);
		EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Started,this,&AIngamePlayerController::CallSprint);
	}
}*/

void AIngamePlayerController::CallMove(const FInputActionValue &Value)
{
	if (PossedPawn)
	{
		PossedPawn->Move(Value); 
	}
}

void AIngamePlayerController::CallLook(const FInputActionValue& Value)
{
	if (PossedPawn)
	{
		PossedPawn->Look(Value);
	}
}

void AIngamePlayerController::CallSprint()
{
	if (PossedPawn)
	{
		PossedPawn->Server_Sprint(); 
	}
}

void AIngamePlayerController::CallDash()
{
	if (PossedPawn)
	{
		PossedPawn->Server_Dash();	
	}
}





// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WOverHead.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"


void UWOverHead::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay)); 
	}
}

void UWOverHead::ShowPlayerName(APawn* Pawn)
{
	if (Pawn)
	{
		APlayerState* PlayerState = Pawn->GetPlayerState();
		if (PlayerState)
		{
			SetDisplayText(PlayerState->GetPlayerName());
		}
	}
	else
	{
		SetDisplayText("No Player");
	}
}

void UWOverHead::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}

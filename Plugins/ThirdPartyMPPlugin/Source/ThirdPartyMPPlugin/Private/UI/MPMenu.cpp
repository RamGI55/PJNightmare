// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPMenu.h"
#include "Components/Button.h"

void UMPMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	// This sets the visibility of the widget. 
	bIsFocusable = true;
	// is it focused? 

	// make the world instance and run GetWorld()
	UWorld* World = GetWorld();
	if (World)
	{
		// bring the playercontroller from the world, agian, the first player controller
		// represents the player in the client. 
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			// Widget Settings. 
			FInputModeUIOnly inputModeUI;
			inputModeUI.SetWidgetToFocus(TakeWidget());
			inputModeUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			// Player Controller settings in the widget. 
			PlayerController->SetInputMode(inputModeUI);
			PlayerController->SetShowMouseCursor(true); 
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainMenuHUD.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Blueprint/UserWidget.h"


AMainMenuHUD::AMainMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/PJNightmare/UI/Menu/WB_MainMenu.WB_MainMenu"));
	if (WidgetClassFinder.Succeeded())
	{
		MainMenuHUDClass = WidgetClassFinder.Class;  
	}
}

void AMainMenuHUD::UIinScreen()
{
	if (MainMenuWidget && MainMenuWidget->IsValidLowLevel())
	{
		return;
	}
	if (MainMenuHUDClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainMenuHUDClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();

			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(MainMenuWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			GetOwningPlayerController()->SetInputMode(InputMode);
			GetOwningPlayerController()->bShowMouseCursor = true;
			
		}
	}
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPMenu.h"
#include "Components/Button.h"
#include "ThirdPartyMPPlugin.h"

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
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			// Player Controller settings in the widget
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true); 
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMPPluginSubSystem>(); 
	}
}

void UMPMenu::HostButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,
			15.0f,
			FColor::Yellow,
			"Hosting button pressed");
	}
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(4, FString("FreeForAll"));
		// Travel Logic.
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Script/Engine.World'/Game/PJNightmare/TestMaps/ShootingRange.ShootingRange'");
			// Temporary Site -> heading to the shooting range. 
		}
	}
}

void UMPMenu::JoinSessionClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,
			15.0f,
			FColor::Yellow,
			"Join button pressed");
	}
}

bool UMPMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false; 
	}
	if (HostGame_TEMP)
	{
		HostGame_TEMP->OnClicked.AddDynamic(this, &UMPMenu::HostButtonClicked);
		// Onclicked is the dynaic delegate that is called when the button is clicked.
	}
	if (JoinGame_TEMP)
	{
		JoinGame_TEMP->OnClicked.AddDynamic(this, &UMPMenu::JoinSessionClicked);
		// Onclicked is the dynaic delegate that is called when the button is clicked.
	}
	return true; 
	
}

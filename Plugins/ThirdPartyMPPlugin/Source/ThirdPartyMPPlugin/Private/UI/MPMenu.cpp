// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPMenu.h"
#include "Components/Button.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
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
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionSubsystem->MultiplayerOnFindSessionComplete.AddUObject(this, &ThisClass::OnFindingSession);
		MultiplayerSessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerSessionSubsystem->MultiplayerOnDestorySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerSessionSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this,&ThisClass::OnStartSession);
	}
}

void UMPMenu::HostButtonClicked()
{
	
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(4, FString("FreeForAll"));
	
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
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->FindSession(10000);
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

void UMPMenu::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMPMenu::OnCreateSession(bool bWasSuccessful)
 {
	// Callback Function
	if (bWasSuccessful)
	{
		// If the session is created, then we can travel to the map. 
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,
				15.0f,
				FColor::Green,
				FString::Printf(TEXT("Session Created Successfully")));
		}
		// Travel Logic.
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/PJNightmare/TestMaps/ShootingRange.ShootingRange?listen");
		}
		
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,
				15.0f,
				FColor::Red,
				FString::Printf(TEXT("Session Created Failed")));
		}
	}
 }

void UMPMenu::OnFindingSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful)
{
	if (MultiplayerSessionSubsystem == nullptr)
	{
		return; 
	}
	
	for (auto Result : SessionResult)
	{
		FString SettingsValue; 
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if (SettingsValue == MatchType)
		{
			MultiplayerSessionSubsystem->JoinSession(Result);
			return; 
		}
	}
}

void UMPMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
		if (OnlineSessionInterface.IsValid())
		{
			FString Address;
			OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession, Address);
		}
	}
}

void UMPMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMPMenu::OnStartSession(bool bWasSuccessful)
{
}

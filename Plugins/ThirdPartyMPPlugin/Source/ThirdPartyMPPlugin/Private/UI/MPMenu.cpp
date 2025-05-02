// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MPMenu.h"
#include "Components/Button.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "ThirdPartyMPPlugin.h"

void UMPMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeofMatch, FString LobbyPath)

{	MatchType = TypeofMatch;
	NumberOfPublicConnections = NumberOfPublicConnections;
	PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath, *MatchType);
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
		FTimerHandle TravelTimerHandle; 
		UWorld* World = GetWorld();
		/*if (World)
		{
			World->ServerTravel("/Game/PJNightmare/TestMaps/ShootingRange?listen");
		}*/
		World->GetTimerManager().SetTimer(
			   TravelTimerHandle, 
			   [World]()
			   {
				   World->ServerTravel("/Game/PJNightmare/TestMaps/ShootingRange?listen");
			   },
			   0.5f,  // Half second delay
			   false
		   );
		FInputModeGameOnly InputClient;
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
	if (!bWasSuccessful || SessionResult.Num() == 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, 
				FString::Printf(TEXT("Find Sessions Failed or No Sessions Found")));
		}
		return;
	}
	
	if (MultiplayerSessionSubsystem == nullptr)
	{
		return; 
	}

	// for debug for information 
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, 
			FString::Printf(TEXT("Found %d sessions"), SessionResult.Num()));
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
	// If we got here, we didn't find a matching session
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, 
			FString::Printf(TEXT("No matching session with MatchType: %s"), *MatchType));
	}
}

void UMPMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (Result!=EOnJoinSessionCompleteResult::Success)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Red, FString::Printf(TEXT("Session Created Failed")));
		}
	}
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
		if (OnlineSessionInterface.IsValid())
		{
			FString Address;
			if (OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, 
						FString::Printf(TEXT("Join Session Success. Connect String: %s"), *Address));
				}
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController)
				{
					PlayerController->ClientTravel(Address, TRAVEL_Absolute);
				}
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, 
						TEXT("Failed to get connect string"));
				}
				
			}
		}
	}
}

void UMPMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMPMenu::OnStartSession(bool bWasSuccessful)
{
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MPPluginSubSystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


UMPPluginSubSystem::UMPPluginSubSystem():
CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
	}
}

#pragma region TravelSession

void UMPPluginSubSystem::CreateSession(int32 NumbPublicConnections, FString MatchType)
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}
	auto ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		OnlineSessionInterface->DestroySession(NAME_GameSession);
		return; 
	}
	CreateSessionCompleteDelegateHandle = OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	TSharedPtr<FOnlineSessionSettings> RecentSessionSettings = MakeShareable(new FOnlineSessionSettings());
	
	RecentSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? false : true;
	RecentSessionSettings->NumPublicConnections = NumbPublicConnections;
	RecentSessionSettings->bAllowJoinInProgress = true;
	RecentSessionSettings->bAllowJoinViaPresence = true;
	RecentSessionSettings->bShouldAdvertise = true;
	RecentSessionSettings->bUsesPresence = true;
	RecentSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	RecentSessionSettings->bUseLobbiesIfAvailable = true;

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	// brought the local player from the controller
	// OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *RecentSessionSettings); 

	if (!OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *RecentSessionSettings))
	{
		OnlineSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
		MultiplayerOnCreateSessionComplete.Broadcast (false); 
	}
}

void UMPPluginSubSystem::FindSession(int32 MaxSearchResults)
{
}

void UMPPluginSubSystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
}

void UMPPluginSubSystem::DestroySession()
{
}

void UMPPluginSubSystem::StartSession()
{
}

#pragma endregion

void UMPPluginSubSystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSessionInterface)
	{
		OnlineSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
		// Start the session
		OnlineSessionInterface->StartSession(SessionName);
	}
	MultiplayerOnCreateSessionComplete.Broadcast(bWasSuccessful);

}

void UMPPluginSubSystem::OnFindSessionsComplete(bool bWasSuccessful)
{
}

void UMPPluginSubSystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UMPPluginSubSystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UMPPluginSubSystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}


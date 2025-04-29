// Fill out your copyright notice in the Description page of Project Settings.


#include "MPPluginSubSystem.h"
#include "OnlineSubsystem.h"


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
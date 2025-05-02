// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"


void ALobbyGameMode::PostLogin(APlayerController* aPlayerController)
{
	Super::PostLogin(aPlayerController);

	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Player # :  %d"), NumberOfPlayers)
			);
			APlayerState* PlayerState = aPlayerController->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				FString PlayerName = PlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
					1,
					60.f,
					FColor::Yellow,
					FString::Printf(TEXT("%s has joined the game!"), *PlayerName)
				);
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	APlayerState* PlayerState =Exiting->GetPlayerState<APlayerState>();
	if (GEngine)
	{
		FString PlayerName = PlayerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(
			1,
			60.f,
			FColor::Yellow,
			FString::Printf(TEXT("%s has joined the game!"), *PlayerName)
			);
	} 
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/IngameGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerController/IngamePlayerController.h"

void AIngameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
	if (NumOfPlayers == 2) // Hardcoded for Testing.
	{
		UWorld* World = GetWorld();
		if (World)
		{
			bUseSeamlessTravel = true;	
			World->ServerTravel(FString("/Game/PJNightmare/TestMaps/ShootingRange?listen")); // Hardcoded for testing purposes. 
		}
	}
}

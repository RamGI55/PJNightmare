// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/IngameGameMode.h"
#include "Character/Player/BasePlayer.h"
#include "PlayerController/IngamePlayerController.h"


AIngameGameMode::AIngameGameMode()
{
	DefaultPawnClass = ABasePlayer::StaticClass();
	PlayerControllerClass = AIngamePlayerController::StaticClass();
}

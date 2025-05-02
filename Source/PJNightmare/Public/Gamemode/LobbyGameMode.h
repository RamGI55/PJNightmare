// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gamemode/BaseGamemode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PJNIGHTMARE_API ALobbyGameMode : public ABaseGamemode
{
	GENERATED_BODY()
	
public :
	virtual void PostLogin(APlayerController* aPlayerController) override;
	virtual void Logout(AController* Exiting) override;
	
	
};

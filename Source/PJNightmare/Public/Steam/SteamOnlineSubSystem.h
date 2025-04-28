// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SteamOnlineSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class PJNIGHTMARE_API USteamOnlineSubSystem : public UObject
{
	GENERATED_BODY()
	
	

public:
	USteamOnlineSubSystem(); 
	
	// pointer to the online session interface;
	TSharedPtr<class IOnlineSession, ESPMode::ThreadSafe> OnlineSessionInterface;
	
};

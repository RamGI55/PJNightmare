// Copyright Epic Games, Inc. All Rights Reserved.

#include "PJNightmareGameMode.h"
#include "PJNightmareCharacter.h"
#include "UObject/ConstructorHelpers.h"

APJNightmareGameMode::APJNightmareGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MPMenu.generated.h"

/**
 * 
 */
class UButton; 
UCLASS()
class THIRDPARTYMPPLUGIN_API UMPMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void MenuSetup(); 
protected:

private: 
	TObjectPtr<UButton> JoinGame_TEMP;

	TObjectPtr<UButton> HostGame_TEMP;

	TObjectPtr<UButton> Exit_TEMP;
};

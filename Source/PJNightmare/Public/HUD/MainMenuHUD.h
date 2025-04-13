// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/BaseHUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
class UUserWidget; 
UCLASS()
class PJNIGHTMARE_API AMainMenuHUD : public ABaseHUD
{
	GENERATED_BODY()

public:
	AMainMenuHUD(); 
	UFUNCTION()
	void UIinScreen();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UUserWidget> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> MainMenuHUDClass;
	
	
};

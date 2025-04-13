// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WMainmenu.generated.h"

/**
 * 
 */
class UButton; 
UCLASS()
class PJNIGHTMARE_API UWMainmenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
	UFUNCTION()
	void OnSoloPlayClicked();
	UFUNCTION()
	void OnQuitClicked(); 

private:
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* BSoloPlay;
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* BHostingGame;
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* BSearchGame;
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	UButton* BQuitGame;
	
	
};

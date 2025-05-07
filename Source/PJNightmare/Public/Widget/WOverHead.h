// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WOverHead.generated.h"

/**
 * 
 */
UCLASS()
class PJNIGHTMARE_API UWOverHead : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DisplayText;

	void SetDisplayText(FString TextToDisplay);
	UFUNCTION(BlueprintCallable)
	void ShowPlayerName(APawn* Pawn);
	

protected:
	virtual void NativeDestruct() override;
};

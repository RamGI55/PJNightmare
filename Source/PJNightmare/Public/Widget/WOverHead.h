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

TObjectPtr<class UTextBlock> DisplayText; 	
	
	
};

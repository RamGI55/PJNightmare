// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_Startupdata.generated.h"

class UPlayerGameplayAbility;
/**
 * 
 */
UCLASS()
class PJNIGHTMARE_API UDataAsset_Startupdata : public UDataAsset
{
	GENERATED_BODY()

public:
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UPlayerGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UPlayerGameplayAbility>> ReactiveAbilities;
	
	
};

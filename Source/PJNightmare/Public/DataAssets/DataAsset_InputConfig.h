// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_InputConfig.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerInputActionConfig
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(Categories = "InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;
};
UCLASS()
class PJNIGHTMARE_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty= "InputTag"))
	TArray<FPlayerInputActionConfig> NativeinputActions;

	UInputAction* FindNativeInputActionByTag(const FGameplayTag InputTag);
};

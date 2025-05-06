// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "EnhancedInputBaseComponent.generated.h"

struct FGameplayTag;
/**
 * 
 */
UCLASS()
class PJNIGHTMARE_API UEnhancedInputBaseComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
};

template <class UserObject, typename CallbackFunc>
void UEnhancedInputBaseComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
	ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input Config Data Asset is null, cannot procced with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction,TriggerEvent,ContextObject,Func);  
	}
}

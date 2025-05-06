// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_InputConfig.h"


UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag InInputTag)
{
	for (const FPlayerInputActionConfig& NativeInputAction : NativeinputActions)
	{
		if (NativeInputAction.InputTag == InInputTag)
		{
			return NativeInputAction.InputAction; 
		}
	}
	
	return nullptr;
}

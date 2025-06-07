// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Player/Shiho/DataAsset_Startupdata.h"

#include "AbilitySystem/BaseAbilitySystem.h"
#include "AbilitySystem/PlayerGameplayAbility.h"


void UDataAsset_Startupdata::GiveToAbilitySystemComponent(UBaseAbilitySystem* InPlayerASCToGive, int32 ApplyLevel)
{
	check(InPlayerASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InPlayerASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InPlayerASCToGive, ApplyLevel);
}

void UDataAsset_Startupdata::GrantAbilities(const TArray<TSubclassOf<UPlayerGameplayAbility>>& InAbilitiesToGive,
	UBaseAbilitySystem* InPlayerASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	for (const TSubclassOf<UPlayerGameplayAbility>& Ability: InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.SourceObject = InPlayerASCToGive->GetAvatarActor();

		InPlayerASCToGive->GiveAbility(AbilitySpec);
		
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "Components/AttackComponent.h"
#include "Engine/SpecularProfile.h"


void UBaseGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (PlayerActivationPolicy == EBasePlayerActiviationPolicy::OnGiven)
	{
		// Activate the ability immediately when given
		if (ActorInfo->IsLocallyControlled() && Spec.IsActive()) // in multiplayer enviornment 
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UBaseGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if (PlayerActivationPolicy == EBasePlayerActiviationPolicy::OnGiven)
		if (ActorInfo->IsLocallyControlled())
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
}

UAttackComponent* UBaseGameplayAbility::GetAttackComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UAttackComponent>();
}

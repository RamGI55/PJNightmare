// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EBasePlayerActiviationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class PJNIGHTMARE_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	
protected:
	// GamePlay Ability System - Given Ability vs End the ability. 
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	
	UPROPERTY(EditDefaultsOnly, Category = "Player Ability")
	EBasePlayerActiviationPolicy PlayerActivationPolicy = EBasePlayerActiviationPolicy::OnTriggered;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/BaseGameplayAbility.h"
#include "PlayerGameplayAbility.generated.h"

class AIngamePlayerController;
class ABasePlayerCharacter;
/**
 * 
 */
UCLASS()
class PJNIGHTMARE_API UPlayerGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	ABasePlayerCharacter* GetPlayerCharacterActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	AIngamePlayerController* GetPlayerControllerActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	UAttackComponent* GetPlayerAttackComponentFromActorInfo();


private:
	mutable TWeakObjectPtr<ABasePlayerCharacter> CachedPlayerCharacter; // Weak object pointer to avoid circular references and memory leaks
	// using mutable to allow access in const functions without modifying the object itself.

	mutable TWeakObjectPtr<AIngamePlayerController> CachedPlayerController; 
	
	
};

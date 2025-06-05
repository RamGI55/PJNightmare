// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PlayerGameplayAbility.h"
#include "Character/Player/BasePlayerCharacter.h"
#include "PlayerController/IngamePlayerController.h"


ABasePlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacterActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<ABasePlayerCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr ; // modern C++ way to check if the weak pointer is valid.
}

AIngamePlayerController* UPlayerGameplayAbility::GetPlayerControllerActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<AIngamePlayerController>(CurrentActorInfo->PlayerController);
	}
	
	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr; // modern C++ way to check if the weak pointer is valid. 
}

UAttackComponent* UPlayerGameplayAbility::GetPlayerAttackComponentFromActorInfo()
{
	return GetPlayerCharacterActorInfo()->GetAttackComponent();
}


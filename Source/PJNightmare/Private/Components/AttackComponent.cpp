// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttackComponent.h"
#include "Character/Player/BasePlayerCharacter.h"
#include "Weapon/BaseWeapon.h"
#include "GameplayTagContainer.h"

#include "Debughelper.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // for now.

}

void UAttackComponent::RegisterTheWeapon(FGameplayTag inWeaponTagtoRegister,
	ABaseWeapon* inWeaponToRegister, bool bRegisterAstEquippedWeapon)
{
	// Register the weapon when the player picks it up. 
	checkf(CharacterCarriedWeapons.Contains(inWeaponTagtoRegister),TEXT("%s has already registered this weapon!"), *inWeaponTagtoRegister.GetTagName().ToString());
	check(inWeaponToRegister)
	
	CharacterCarriedWeapons.Emplace(inWeaponTagtoRegister, inWeaponToRegister);

	if (bRegisterAstEquippedWeapon)
	{
		CurrentEquippedWeaponTag = inWeaponTagtoRegister; 
	}

	const FString WeaponString = FString::Printf(TEXT("A Weapon named %s has been registered tag name %s"), *inWeaponToRegister->GetName(), *inWeaponTagtoRegister.GetTagName().ToString());
	Debug::Print(WeaponString); 
}

ABaseWeapon* UAttackComponent::GetCharacterCarriedWeaponByTag(FGameplayTag inWeaponTag) const
{
	if (CharacterCarriedWeapons.Contains (inWeaponTag))
	{
		if (ABaseWeapon* const* FindWeapon = CharacterCarriedWeapons.Find(inWeaponTag))
		{
			return *FindWeapon; 
		}
		
	}
	return nullptr;
}

ABaseWeapon* UAttackComponent::GetCharacterCarriedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()){return nullptr; }
	
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag); 
}



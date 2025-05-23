	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


class ABasePlayerCharacter;
class ABaseWeapon;
struct FGameplayTag;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PJNIGHTMARE_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	// Register when the weapon is picked up. 
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RegisterTheWeapon(FGameplayTag inWeaponTagtoRegister,
		ABaseWeapon* inWeapontoRegister,
		bool bRegisterAstEquippedWeapon = false);

	UFUNCTION(BlueprintCallable , Category = "Combat")
	ABaseWeapon* GetCharacterCarriedWeaponByTag(FGameplayTag inWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	ABaseWeapon* GetCharacterCarriedWeapon() const;

protected:
	
public:
	UPROPERTY(BlueprintReadWrite, Category="Combat")
	FGameplayTag CurrentEquippedWeaponTag; 
protected:
	TMap<FGameplayTag, ABaseWeapon*> CharacterCarriedWeapons; 
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitysystemInterface.h"
#include "BaseCharacter.generated.h"

class UBaseAbilitySystem;
class UBaseAbilityAttributeSet;
UCLASS()
class PJNIGHTMARE_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
	// IAbilitySystemInterface //
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	
	virtual void PossessedBy(AController* NewController) override;

	// Getters // 
	FORCEINLINE UBaseAbilitySystem* GetAbilitySystem() const { return AbilitySystemComponent; }
	FORCEINLINE UBaseAbilityAttributeSet* GetAbilityAttributeSet() const { return AbilityAttributeSet; }

protected:
	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category= "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBaseAbilitySystem> AbilitySystemComponent;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category= "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBaseAbilityAttributeSet> AbilityAttributeSet;
public:

	
};

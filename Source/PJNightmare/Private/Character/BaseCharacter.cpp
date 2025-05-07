// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "AbilitySystem/BaseAbilitySystem.h"
#include "AbilitySystem/BaseAbilityAttributeSet.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false; 

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystem>(TEXT("BaseAbilitySystem"));

	AbilityAttributeSet = CreateDefaultSubobject<UBaseAbilityAttributeSet>(TEXT("BaseAttributeSet"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetAbilitySystemComponent();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); // Owner Actor might be different from the Actor itself! 
	}
}

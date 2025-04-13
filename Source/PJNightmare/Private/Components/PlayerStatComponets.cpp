// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerStatComponets.h"


// Sets default values for this component's properties
UPlayerStatComponets::UPlayerStatComponets()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
	// ...
}

float UPlayerStatComponets::GetHealth()
{
	return fHealth; 
}

void UPlayerStatComponets::SetHealth(float inHealth)
{
	fHealth = inHealth;
}

float UPlayerStatComponets::GetMaxHealth()
{
	return fMaxHealth;
}

float UPlayerStatComponets::GetSpeed()
{
	return fCharacterSpeed; 
}

void UPlayerStatComponets::SetSpeed(float inSpeed)
{
	fCharacterSpeed = inSpeed;
}

float UPlayerStatComponets::GetDefence()
{
	return fDefence; 
}

void UPlayerStatComponets::SetDefence(float inDefence)
{
	fDefence = inDefence;
}

float UPlayerStatComponets::GetCritRate()
{
	return fCritRate;
}

float UPlayerStatComponets::GetCritDamage()
{
	return fCritDamage;
}

void UPlayerStatComponets::TakeDamage(float inDamage)
{
	fHealth = fHealth - inDamage;
	// dispatcher
	
}

void UPlayerStatComponets::Basicintialiser()
{
	fHealth = fMaxHealth;
	fMainSkillGauge = fMaxMainSkillGauge;
	fSubSkillGauge = fMaxSubSkillGauge;
	fUltSkillGauge= fMaxUltSkillGauge * 0.4;
	
}




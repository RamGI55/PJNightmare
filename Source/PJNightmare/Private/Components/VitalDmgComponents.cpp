// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VitalDmgComponents.h"


// Sets default values for this component's properties
UVitalDmgComponents::UVitalDmgComponents()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UVitalDmgComponents::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	return DamageAmount; 
}




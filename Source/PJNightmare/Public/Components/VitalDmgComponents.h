// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VitalDmgComponents.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PJNIGHTMARE_API UVitalDmgComponents : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVitalDmgComponents();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

protected:
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	float fHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	float fMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	int32 iArmorLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	int32 iMaxArmorlevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	float fArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	float fMaxArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	bool isInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vital")
	bool isFainted; 
	

protected:
	
		
	
};

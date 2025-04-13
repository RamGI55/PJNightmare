// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponets.generated.h"

UENUM(BlueprintType)
enum class EPlayerClass : uint8
{
	Sentinel,
	Vanguard,
	Support,
	Enforcer
};

UENUM(BlueprintType)
enum class EPlayerElement : uint8
{
	Acid,
	Blaze,
	Physical,
	Frozen,
	Electric,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PJNIGHTMARE_API UPlayerStatComponets : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatComponets();
#pragma region Getters
	
	UFUNCTION()
	float GetHealth();

	UFUNCTION()
	void SetHealth(float inHealth);

	UFUNCTION()
	float GetMaxHealth();

	UFUNCTION()
	float GetSpeed();

	UFUNCTION()
	void SetSpeed(float inSpeed);

	UFUNCTION()
	float GetDefence();

	UFUNCTION()
	void SetDefence(float inDefence);

	UFUNCTION()
	float GetCritRate();

	UFUNCTION()
	float GetCritDamage();
	
#pragma endregion

	UFUNCTION()
	void TakeDamage(float inDamage);
	
	UFUNCTION()
	void Basicintialiser(); 


protected:
#pragma region Dispature 

	

#pragma endregion 
	
private:


public:

private:
	// Dynamic Player Stats //
#pragma region PlayerStat
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fCharacterSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fCritRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fCritDamage; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fMainSkillGauge;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fMaxMainSkillGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fSubSkillGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fMaxSubSkillGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fUltSkillGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fMaxUltSkillGauge;

	// Static Player Stats //
#pragma endregion Player Stat
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	float fBasicAttack; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	EPlayerClass PlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess=true))
	EPlayerElement PlayerElement;
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FCharacterStats.generated.h"

/**
 * 
 */

enum class EPlayerClass : uint8;
enum class EPlayerElement : uint8;
USTRUCT(BlueprintType)
struct FPlayerStat : public FTableRowBase
{
	GENERATED_BODY()
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	EPlayerClass PlayerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	EPlayerElement Element;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float fHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float fDefence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float fBasicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float fCharacterSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float fCritDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float fMainSkillGauge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float fSubSkillGauge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float fUltSkillGauge;
	*/
	
};
UCLASS()
class PJNIGHTMARE_API UFCharacterStats : public UObject
{
	GENERATED_BODY()
	
	
	
	
};

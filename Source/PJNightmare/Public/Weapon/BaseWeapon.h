// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
UENUM(Blueprintable)
enum class EWeaponState : uint8
{
	EWS_InitialState UMETA(DisplayName = "Initial State"), // Never been picked up
	EWS_Equipped UMETA(DisplayName = "Equipped State"),
	EWS_Dropped UMETA(DisplayName = "Dropped State"),

	EWS_Max UMETA(DisplayName = "DefaultMax")
};

UENUM(Blueprintable)
enum class EWeaponClassification : uint8
{
	EWC_Unknown UMETA(DisplayName = "Unknown"),
	EWC_Rifle UMETA(DisplayName = "Rifle"),
	EWC_SMG UMETA(DisplayName = "SMG"),
	EWC_Sniper UMETA(DisplayName = "Sniper"),
	EWC_DMR UMETA(DisplayName = "DMR"),
	EWC_Shotgun UMETA(DisplayName = "Shotgun"),
	EWC_Pistol UMETA(DisplayName ="Pistol"),
	EWC_Knife UMETA(DisplayName = "Knife"),
	EWC_Misc UMETA(DisplayName = "Misc")
};
UCLASS()
class PJNIGHTMARE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();
protected:
	virtual void BeginPlay() override;
private:
	
public:	
	// Sets default values for this actor's properties
	
	
protected:
	
private:
	UPROPERTY(VisibleAnywhere, Category = "WeaponProperties")
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "WeaponProperties")
	TObjectPtr<USphereComponent> AreaSphere;
	
	UPROPERTY(EditAnywhere, Blueprintable)
	EWeaponState WeaponState;

	UPROPERTY(EditAnywhere, Blueprintable)
	EWeaponClassification WeaponClass; 
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UWidgetComponent;
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

	UFUNCTION()
	void ShowPickupWidget(bool bShowWidget); 
	

	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }

protected:
	virtual void BeginPlay() override;

	

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& Hit
	);

	// need the function for overlap has been ended.
	UFUNCTION()
	virtual void OnSphereOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	); 
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

	UPROPERTY(EditAnywhere, Blueprintable, Category = "Widget")
	TObjectPtr<UWidgetComponent> WeaponPickupWidget;	
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer.generated.h"


class AIngamePlayerController;
class UPlayerStatComponets; 
class UPlayerSkillComponent;
class USpringArmComponent;
class UCameraComponent;
class UIngameController;
class UInputMappingContext;
class UInputComponent;
class UInputAction;
class UPlayerStatComponets;
class UPlayerSkillComponent;
class UVitalDmgComponents;
class USkeletalMeshComponent;
struct FInputActionValue; 
UENUM(BlueprintType)
enum class EArmed : uint8
{
	Unarmed,
	Autoarmed,
	Semiarmed,
	Meleearmed,
	OnVehicle,
	
};

UCLASS()
class PJNIGHTMARE_API ABasePlayer : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ABasePlayer();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);


#pragma region RPC
	UFUNCTION(Server, Reliable)
	void Server_Sprint();
	
	UFUNCTION(NetMulticast, Reliable)
	void Multi_Sprint();
	
	UFUNCTION(Server, Reliable)
	void ServerAiming();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Aiming();

	UFUNCTION(Server, Reliable)
	void Server_StopAiming();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_StopAiming();
	
	UFUNCTION(Server, Reliable)
	void Server_Dash();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Dash();
	
	UFUNCTION(Server, Reliable)
	void Server_Fire();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Fire();


#pragma endregion
protected :

#pragma region Dispature

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

protected:
#pragma region Montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UAnimMontage> MainAbilityMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UAnimMontage> SubAbilityMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UAnimMontage> UltAbilityMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UAnimMontage> StunMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UAnimMontage> FaintedMontage;
#pragma endregion
	
private:
	UPROPERTY()
	TObjectPtr<UPlayerSkillComponent> SkillComponent;

	UPROPERTY()
	UPlayerStatComponets* StatComponent; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

#pragma region Input
	UPROPERTY()
	TObjectPtr<UInputMappingContext> InputContext;
	
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMapping;
	
	UPROPERTY()
	TObjectPtr<AIngamePlayerController> PlayerController; 
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY()
	TObjectPtr<UInputMappingContext> IC_Character;

	UPROPERTY()
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY()
	TObjectPtr<UInputAction> IA_Zoom;

	UPROPERTY()
	TObjectPtr<UInputAction> IA_Dash;
	
	UPROPERTY()
	TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY()
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY()
	TObjectPtr<UInputAction> IA_Run; 
#pragma endregion

#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerStatComponets> PlayerStatComponets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVitalDmgComponents> DamageComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerSkillComponent> PlayerSkillComponent;

	
	
#pragma endregion
};





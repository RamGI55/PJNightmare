// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Debughelper.h" 
#include "BasePlayerCharacter.generated.h"


class UAttackComponent;
class ABaseWeapon;
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
class UWidgetComponent;
struct FInputActionValue;
/**
 * 
 */

UCLASS()
class PJNIGHTMARE_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABasePlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void tick(float DeltaTime) ; 
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
private:

public:
	UFUNCTION (BlueprintCallable)
	void OnRep_OverlappingWeapon(ABaseWeapon* LastWeapon);
	
	void SetOverlappingWeapon (ABaseWeapon* Weapon);
protected:

private:
#pragma region components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> OverheadWidget;
	
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon, EditAnywhere, BlueprintReadWrite, Category = "WeaponOverlapped", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseWeapon> OverlappedWeapon;

	UPROPERTY()
	TObjectPtr<UAttackComponent> AttackComponent;

	// for VRM Setting, using this variable to control VRM physiscs setting. 
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Authority Setting", meta=(AllowPrivateAccess = "true"))
	bool isRuninServer;
	
#pragma endregion

#pragma region Inputs
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Character",meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look (const FInputActionValue& InputActionValue);
	void Input_Run (const FInputActionValue& InputActionValue);
	void Input_Attack (const FInputActionValue& InputActionValue); 

	
#pragma endregion
	
};





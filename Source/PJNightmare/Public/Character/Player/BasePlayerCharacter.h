// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
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

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
private:

public:

protected:

private:
#pragma region components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera; 
#pragma endregion

#pragma region Inputs
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Character",meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);

	void Input_Look (const FInputActionValue& InputActionValue);
#pragma endregion
	
};

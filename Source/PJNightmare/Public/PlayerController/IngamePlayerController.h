// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/BasePC.h"
#include "IngamePlayerController.generated.h"

/**
 * 
 */

class ABasePlayer; 
class UInputAction; 
struct FInputActionValue;

UCLASS()
class PJNIGHTMARE_API AIngamePlayerController : public ABasePC
{
	GENERATED_BODY()
public:
	AIngamePlayerController();

virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	
	/*virtual void SetupInputComponent(class UIInputComponent* PlayerInputComponent);*/

	UFUNCTION()
	void CallMove(const FInputActionValue &Value);

	UFUNCTION()
	void CallLook(const FInputActionValue &Value);

	UFUNCTION()
	void CallSprint();

	UFUNCTION()
	void CallDash(); 

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MovementInput;
	
protected:
	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	ABasePlayer* PossedPawn; 
};

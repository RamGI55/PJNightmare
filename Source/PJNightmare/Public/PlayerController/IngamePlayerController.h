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
class UInputMappingContext; 
struct FInputActionValue;

UCLASS()
class PJNIGHTMARE_API AIngamePlayerController : public ABasePC
{
	GENERATED_BODY()
public:
	AIngamePlayerController();

virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void GetMappings(); 
protected:
	
	/*virtual void SetupInputComponent(class UIInputComponent* PlayerInputComponent);*/


public:
	UPROPERTY()
	UInputMappingContext* IngameDefaultMapping; 
	
protected:
	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	ABasePlayer* PossedPawn; 
};


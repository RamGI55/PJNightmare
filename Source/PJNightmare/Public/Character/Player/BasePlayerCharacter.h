// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent; 
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
	
	
	
	
};

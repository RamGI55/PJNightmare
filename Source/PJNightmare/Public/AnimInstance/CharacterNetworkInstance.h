// Fill out your copyright notice in the Description page of Project Settings.
// This class for the component class VRM4Uaniminstance properly work in the networking environement.
// Must be reviewed and tested. 

// 
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterNetworkInstance.generated.h"

/**
 * 
 */
UCLASS()
class PJNIGHTMARE_API UCharacterNetworkInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	UCharacterNetworkInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:
	// Network state Variables to send the anim instance.
	UPROPERTY (BlueprintReadOnly, Category = "Network")
	bool isServer;

	UPROPERTY (BlueprintReadOnly, Category = "Network")
	bool isLocallyControlled;

	UPROPERTY (BlueprintReadOnly, Category = "Network")
	bool ShouldRunTheVRMPhysics;

	UPROPERTY()
	TObjectPtr<APawn> CachedPawn;

public:

	// Getters 
	UFUNCTION(BlueprintCallable, BlueprintPure,Category="Network")
	bool ShouldRunVrmPhysics() const { return ShouldRunTheVRMPhysics; }

	UFUNCTION(BlueprintCallable, BlueprintPure,Category="Network")
	bool isServerInstance()const {return isServer;}
	
};

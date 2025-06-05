// Fill out your copyright notice in the Description page of Project Settings.
// DEPRECATED - doesn't work for now, switch to the component system. 

#include "AnimInstance/CharacterNetworkInstance.h"
#include "GameFramework/Pawn.h"
#include "Debughelper.h"


UCharacterNetworkInstance::UCharacterNetworkInstance():
ShouldRunTheVRMPhysics(true),
isServer(false),
isLocallyControlled(false)
{
	
}

void UCharacterNetworkInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CachedPawn = TryGetPawnOwner();

	if (CachedPawn)
	{
		isServer = CachedPawn->HasAuthority();
		isLocallyControlled = CachedPawn->IsLocallyControlled();
		ShouldRunTheVRMPhysics = isServer;

		Debug::Print(FString::Printf(TEXT("NetworkAnim Init - Server: %s, Local: %s, VRM: %s"), 
			isServer ? TEXT("YES") : TEXT("NO"),
			isLocallyControlled ? TEXT("YES") : TEXT("NO"),
			ShouldRunTheVRMPhysics ? TEXT("YES") : TEXT("NO")), FColor::Green);
		
	}
}

void UCharacterNetworkInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CachedPawn)
	{
		isServer = CachedPawn->HasAuthority();
		isLocallyControlled = CachedPawn->IsLocallyControlled();
		ShouldRunTheVRMPhysics = isServer; 
	}
}

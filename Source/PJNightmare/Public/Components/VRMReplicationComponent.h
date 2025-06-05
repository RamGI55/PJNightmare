
//////////////////////////////////////////////////////////////////
// The replication system to sync VRM4U animation/physics data  //
// In the networking enviornment.                               // 
//////////////////////////////////////////////////////////////////

#pragma once

#include "CoreMinimal.h"
#include "VrmMetaObject.h"
#include "Components/ActorComponent.h"
#include "VRMReplicationComponent.generated.h"

struct FVRMAnimationMeta;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class PJNIGHTMARE_API UVRMReplicationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRMReplicationComponent();
	virtual void BeginPlay() override;
	/*virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;*/

	/*UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "VRM Network")
	void NetMulticast_SetBlendShape(const FString& BlendShapeName, float inValue);*/

	/*UFUNCTION(BlueprintCallable, Category = "VRM Network")
	void Network_SpringBone(const FVector& Gravity, float inStiffness, bool isEnabled);

	UFUNCTION(NetMulticast, Unreliable , Category = "VRM Network")
	void NetMulticast_PhysicsState(bool isSimulated, float inBlendWeight)*/

protected:
	// Called when the game starts



public:	
	/*UPROPERTY(BluprintReadOnly, Category = "VRM")
	FVRMAnimationMeta ReplicatedAnimMeta; */

	
protected:
	
		
	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerSkillComponent.h"


// Sets default values for this component's properties
UPlayerSkillComponent::UPlayerSkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPlayerSkillComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerSkillComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool UPlayerSkillComponent::UseKill(int32 Skillindex, AActor* TargetActor)
{
	return false;
}

bool UPlayerSkillComponent::CanUseSkill(int32 Skillindex) const
{
	return false;
}

bool UPlayerSkillComponent::isSkillUnlocked(int32 Skillindex) const
{
	return false; 
}

void UPlayerSkillComponent::UpgradeSkill(int32 Skillindex)
{
}

void UPlayerSkillComponent::UnlockSkill(int32 Skillindex)
{
}

float UPlayerSkillComponent::GetSkillCooldownRemaining(int32 Skillindex) const
{
	return 0.0f;
}

float UPlayerSkillComponent::GetSkillCooldownPercent(int32 SkillIndex) const
{
	return 0.0f;
}

int32 UPlayerSkillComponent::GetSkillCurrentLevel(int32 Skillindex) const
{
	return 0;
}

const FSkillData& UPlayerSkillComponent::GetSkillData(int32 Skillindex) const
{
	if (Skills.IsValidIndex(Skillindex))
	{
		return Skills[Skillindex];
		
	}
	static FSkillData EmptySkill; // Static lives through program execution
	return EmptySkill;
}

void UPlayerSkillComponent::CancelCurrentSkil()
{
}

void UPlayerSkillComponent::UpdateSkillwithCharacterLevel(int32 CharacterLevel)
{
}

inline void UPlayerSkillComponent::Server_UseSkill_Implementation(int32 SkillIndex, AActor* TargetActor)
{
}

inline bool UPlayerSkillComponent::Server_UseSkill_Validate(int32 SkillIndex, AActor* TargetActor)
{
	return SkillIndex >= 0 && SkillIndex < Skills.Num(); 
}

inline void UPlayerSkillComponent::Multicast_PlaySkillEffects_Implementation(int32 SkillIndex, AActor* TargetActor)
{
}

inline bool UPlayerSkillComponent::Multicast_PlaySkillEffects_Validate(int32 SkillIndex, AActor* TargetActor)
{
	return SkillIndex >= 0 && SkillIndex < Skills.Num(); 
}

inline void UPlayerSkillComponent::Server_UpgradeSkill_Implementation(int32 SkillIndex)
{
}

inline bool UPlayerSkillComponent::Server_UpgradeSkill_Validate(int32 SkillIndex)
{
	return SkillIndex >= 0 && SkillIndex < Skills.Num(); 
}

inline void UPlayerSkillComponent::Server_UnlockSkill_Implementation(int32 SkillIndex)
{
}

inline bool UPlayerSkillComponent::Server_UnlockSkill_Validate(int32 SkillIndex)
{
	return SkillIndex >= 0 && SkillIndex < Skills.Num(); 
}

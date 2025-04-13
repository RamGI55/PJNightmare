// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSkillComponent.generated.h"

class UAnimMontage;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Main,
	Sub,
	Passive,
	Ultimate
};

UENUM(BlueprintType)
enum class ESkillTargetType : uint8
{
	Self,
	SingleTarget,
	AoE,
	Projectile
};

USTRUCT(BlueprintType)
struct FSkillData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESkillType SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESkillTargetType SkillTargetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float fCooldown;

	// Animation and effects
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> SkillMontage;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UGameplayEffect> SkillEffect;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> SkillSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MontageSection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float fEffectDuration; 

	// Damage information 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float fBaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float fScaleFactor;

	// Targeting system. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AOERadius; 

};

USTRUCT()
struct FSkillInstance
{
	GENERATED_BODY()

	UPROPERTY()
	int32 SkillIndex;

	UPROPERTY()
	float CooldownRemaining;

	UPROPERTY()
	int32 Currentlevel;

	UPROPERTY()
	bool bIsUnlocked;

	FSkillInstance():SkillIndex(0), CooldownRemaining(0.0f), Currentlevel(1), bIsUnlocked(false)
	{
		
	}
	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PJNIGHTMARE_API UPlayerSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerSkillComponent();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	// core skill functions
	
	UFUNCTION(BlueprintCallable, Category ="Skills")
	bool UseKill(int32 Skillindex, AActor* TargetActor = nullptr);

	UFUNCTION(BlueprintCallable, Category="Skills")
	bool CanUseSkill(int32 Skillindex) const;
	
	UFUNCTION(Category = "Skills")
	bool isSkillUnlocked(int32 Skillindex) const; 

	UFUNCTION(BlueprintCallable, Category="Skills")
	void UpgradeSkill(int32 Skillindex);

	UFUNCTION(BlueprintCallable, Category="Skills")
	void UnlockSkill(int32 Skillindex);

	UFUNCTION(Category = "Skills")
	float GetSkillCooldownRemaining(int32 Skillindex) const;

	UFUNCTION(Category = "Skills")
	float GetSkillCooldownPercent(int32 SkillIndex) const;

	UFUNCTION(Category = "Skills")
	int32 GetSkillCurrentLevel(int32 Skillindex) const;

	UFUNCTION(Category = "Skills")
	const FSkillData& GetSkillData(int32 Skillindex) const;

	UFUNCTION(Category = "Skills")
	int32 GetNumSkills() const {return Skills.Num();}

	// Cancelled or interrupted skill 
	UFUNCTION(BlueprintCallable, Category="Skills")
	void CancelCurrentSkil();

	// Level influence on the character skill 
	UFUNCTION(BlueprintCallable, Category="Skills")
	void UpdateSkillwithCharacterLevel(int32 CharacterLevel);

	// For UI Binding

protected:

#pragma region RPCs
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UseSkill(int32 SkillIndex, AActor* TargetActor);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multicast_PlaySkillEffects(int32 SkillIndex, AActor* TargetActor);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpgradeSkill(int32 SkillIndex);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UnlockSkill(int32 SkillIndex); 
#pragma endregion

protected:

	
	UPROPERTY(EditDefaultsOnly, Category="Skills")
	TArray<FSkillData> Skills;

	UPROPERTY(EditDefaultsOnly, Replicated, Category="Skills")
	TArray<FSkillInstance> SkillInstances;

	UPROPERTY(EditDefaultsOnly, Replicated, Category="Skills")
	int32 CurrentSkillIndex;

	UPROPERTY(EditDefaultsOnly,Replicated, Category="Skills")
	bool bIsUsingSkill;
	
private:
	
public:
	
	
private:
};




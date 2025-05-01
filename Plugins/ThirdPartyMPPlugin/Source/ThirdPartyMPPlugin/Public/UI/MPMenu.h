// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPPluginSubSystem.h"
#include "Blueprint/UserWidget.h"
#include "MPMenu.generated.h"

class UMPPluginSubSystem;
class UButton; 
UCLASS()
class THIRDPARTYMPPLUGIN_API UMPMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();
	
protected:
	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION() 
	void JoinSessionClicked(); 

private:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

public:

protected:
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindingSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
private:
	// The subsystem designed to handle all online session functionality.
	TObjectPtr<UMPPluginSubSystem> MultiplayerSessionSubsystem;
	
	UPROPERTY (meta = (BindWidget))
	TObjectPtr<UButton> JoinGame_TEMP;

	UPROPERTY (meta = (BindWidget))
	TObjectPtr<UButton> HostGame_TEMP;

	UPROPERTY (meta = (BindWidget))
	TObjectPtr<UButton> Exit_TEMP;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WMainmenu.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"


bool UWMainmenu::Initialize()
{
	
	bool Success = Super::Initialize();
	if (!Success) return false;
	if (BQuitGame)
	{
		BQuitGame->OnClicked.AddDynamic(this, &UWMainmenu::OnQuitClicked);
	}

	return true; 
	
}

void UWMainmenu::OnSoloPlayClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		
	}
}

void UWMainmenu::OnQuitClicked()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false); 
	}
}

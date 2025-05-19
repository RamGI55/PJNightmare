// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "character/Player/BasePlayerCharacter.h"


// Sets default value
ABaseWeapon::ABaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true; // Actor replicatation setting. 

	// initialise the root component 
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMeshComponent); 

	// Collision Setting
	WeaponMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Weapon collision mesh settings. 
	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	// Widget Construction
	WeaponPickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	WeaponPickupWidget->SetupAttachment(RootComponent);
	if (WeaponPickupWidget)
	{
		WeaponPickupWidget->SetVisibility(false); 
	}
	
		
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) // if on the server.
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::OnSphereOverlap);

		// only check in the server. 
	}
}

// Overlap function

void ABaseWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	TObjectPtr<ABasePlayerCharacter> PlayerCharacter = Cast<ABasePlayerCharacter>(OtherActor);
	if (PlayerCharacter && WeaponPickupWidget)
	{
		WeaponPickupWidget->SetVisibility(true); 
	}
}

void ABaseWeapon::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TObjectPtr<ABasePlayerCharacter> PlayerCharacter = Cast<ABasePlayerCharacter>(OtherActor);
	if (PlayerCharacter && WeaponPickupWidget)
	{
		WeaponPickupWidget->SetVisibility(false);
	} 
}


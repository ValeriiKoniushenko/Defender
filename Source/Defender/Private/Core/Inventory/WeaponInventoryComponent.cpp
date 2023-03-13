// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/WeaponInventoryComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

UWeaponInventoryComponent::UWeaponInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ABaseWeapon* UWeaponInventoryComponent::AddWeapon(ABaseWeapon* Weapon)
{
	return Weapons[Weapons.Add(Weapon)];
}

ABaseWeapon* UWeaponInventoryComponent::GetWeapon(uint32 Index)
{
	if (!Weapons.IsValidIndex(Index))
	{
		UE_LOG(LogBaseWeapon, Fatal, TEXT("Invalid Weapon Index"));
	}
	
	return Weapons[Index];
}

int32 UWeaponInventoryComponent::CountOfWeapons() const
{
	return Weapons.Num();
}


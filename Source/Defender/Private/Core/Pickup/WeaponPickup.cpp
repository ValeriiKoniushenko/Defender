// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Pickup/WeaponPickup.h"

#include "Core/Character/BaseCharacter.h"
#include "Core/Weapon/BaseWeapon.h"

void AWeaponPickup::Pickup(ABaseCharacter* BaseCharacter)
{
	Super::Pickup(BaseCharacter);
	
	BaseCharacter->AddWeaponToInventory(WeaponClass, WeaponSettings);
}

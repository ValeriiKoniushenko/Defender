// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Pickup/BasePickup.h"
#include "Core/Weapon/BaseWeapon.h"
#include "WeaponPickup.generated.h"

class ABaseWeapon;
/**
 * 
 */
UCLASS()
class DEFENDER_API AWeaponPickup : public ABasePickup
{
	GENERATED_BODY()
public:
	virtual void Pickup(ABaseCharacter* BaseCharacter) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere)
	FWeaponSettings WeaponSettings;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponInventoryComponent.generated.h"


class ABaseWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEFENDER_API UWeaponInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	ABaseWeapon* AddWeapon(ABaseWeapon* Weapon);
	ABaseWeapon* GetWeapon(uint32 Index);
	int32 CountOfWeapons() const;
	
protected:
	virtual void BeginPlay() override;
		
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ABaseWeapon*> Weapons;
};

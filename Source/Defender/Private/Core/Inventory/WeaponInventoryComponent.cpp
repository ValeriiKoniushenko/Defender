// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/WeaponInventoryComponent.h"

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


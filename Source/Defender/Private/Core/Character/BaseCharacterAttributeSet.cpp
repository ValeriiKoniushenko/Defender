// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/BaseCharacterAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UBaseCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseCharacterAttributeSet, Health, OldHealth);
}

void UBaseCharacterAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseCharacterAttributeSet, Stamina, OldStamina);
}

void UBaseCharacterAttributeSet::OnRep_MaxWalkSpeed(const FGameplayAttributeData& OldMaxWalkSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseCharacterAttributeSet, MaxWalkSpeed, OldMaxWalkSpeed);
}

void UBaseCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBaseCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseCharacterAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseCharacterAttributeSet, MaxWalkSpeed, COND_None, REPNOTIFY_Always);
}

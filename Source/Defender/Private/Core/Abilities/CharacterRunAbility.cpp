// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Abilities/CharacterRunAbility.h"

#include "Core/Character/BaseCharacter.h"

void UCharacterRunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (RunEffect)
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
		{
			FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
			GameplayEffectContextHandle.AddSourceObject(this);

			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
				RunEffect, 1, GameplayEffectContextHandle);

			if (SpecHandle.IsValid())
			{
				ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
			}
		}
	}
}
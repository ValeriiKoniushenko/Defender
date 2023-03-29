// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Abilities/CharacterWalkAbility.h"

#include "Core/Character/BaseCharacter.h"

UCharacterWalkAbility::UCharacterWalkAbility()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("character.moving.walk")));
}

void UCharacterWalkAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (WalkEffect)
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
		{
			FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
			GameplayEffectContextHandle.AddSourceObject(this);

			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
				WalkEffect, 1, GameplayEffectContextHandle);

			if (SpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

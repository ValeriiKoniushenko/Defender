// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Abilities/CharacterRunAbility.h"

#include "Core/Character/BaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogUCharacterRunAbility, All, All)

UCharacterRunAbility::UCharacterRunAbility()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("character.moving.run")));
}

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
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
			else
			{
				UE_LOG(LogUCharacterRunAbility, Error, TEXT("Can't create Outgoing Spec handle"));
			}
		}
		else
		{
			UE_LOG(LogUCharacterRunAbility, Error, TEXT("Can't get an ability system component from an actor info"));
		}
	}
	else
	{
		UE_LOG(LogUCharacterRunAbility, Error, TEXT("RunEffect in NULL. Set RunEffect throug the blueprint class"));
	}
}

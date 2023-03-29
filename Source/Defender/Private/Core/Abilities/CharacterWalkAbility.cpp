// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Abilities/CharacterWalkAbility.h"

#include "Core/Character/BaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogUCharacterWalkAbility, All, All)

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
			else
			{
				UE_LOG(LogUCharacterWalkAbility, Error, TEXT("Can't create Outgoing Spec handle"));
			}
		}
		else
		{
			UE_LOG(LogUCharacterWalkAbility, Error, TEXT("Can't get an ability system component from an actor info"));
		}
	}
	else
	{
		UE_LOG(LogUCharacterWalkAbility, Error, TEXT("WalkEffect in NULL. Set WalkEffect throug the blueprint class"));
	}
}

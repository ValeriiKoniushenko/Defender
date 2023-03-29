// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Abilities/CharacterJogAbility.h"

#include "Core/Character/BaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogUCharacterJogAbility, All, All)

UCharacterJogAbility::UCharacterJogAbility()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("character.moving.jog")));
}

void UCharacterJogAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (JogEffect)
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
		{
			FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
			GameplayEffectContextHandle.AddSourceObject(this);

			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
				JogEffect, 1, GameplayEffectContextHandle);

			if (SpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
			else
			{
				UE_LOG(LogUCharacterJogAbility, Error, TEXT("Can't create Outgoing Spec handle"));
			}
		}
		else
		{
			UE_LOG(LogUCharacterJogAbility, Error, TEXT("Can't get an ability system component from an actor info"));
		}
	}
	else
	{
		UE_LOG(LogUCharacterJogAbility, Error, TEXT("JogEffect in NULL. Set JogEffect throug the blueprint class"));
	}
}

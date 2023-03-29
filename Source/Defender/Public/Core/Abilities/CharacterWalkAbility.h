// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharacterWalkAbility.generated.h"

/**
 * 
 */
UCLASS()
class DEFENDER_API UCharacterWalkAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UCharacterWalkAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Effects)
	TSubclassOf<UGameplayEffect> WalkEffect;
};

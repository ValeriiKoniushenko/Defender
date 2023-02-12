// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseCharacterAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class DEFENDER_API UBaseCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	FGameplayAttributeData Health;
	FGameplayAttributeData Stamina;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class DEFENDER_API UCharacterHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* StaminaProgressBar;
};

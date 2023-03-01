// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "BaseHUD.generated.h"

class UCharacterHUDWidget;
class UGameMenuUserWidget;
class UUserWidget;

UCLASS()
class DEFENDER_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	bool ToggleMenu();

	UUserWidget* CrosshairWidget;
	UCharacterHUDWidget* CharacterHUDWidget;
	UGameMenuUserWidget* GameMenuUserWidget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	TSubclassOf<UGameMenuUserWidget> GameMenuUserWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	TSubclassOf<UCharacterHUDWidget> CharacterHUDWidgetClass;
};

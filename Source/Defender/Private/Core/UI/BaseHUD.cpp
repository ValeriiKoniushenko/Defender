// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UI/BaseHUD.h"

#include "Blueprint/UserWidget.h"
#include "Core/UI/CharacterHUDWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	check(CrosshairWidgetClass)
	CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
	check(CrosshairWidget)
	CrosshairWidget->AddToViewport();

	check(CharacterHUDWidgetClass)
	CharacterHUDWidget = CreateWidget<UCharacterHUDWidget>(GetWorld(), CharacterHUDWidgetClass);
	check(CharacterHUDWidget)
	CharacterHUDWidget->AddToViewport();
}

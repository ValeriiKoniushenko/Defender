// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UI/BaseHUD.h"

#include "Blueprint/UserWidget.h"
#include "Core/UI/CharacterHUDWidget.h"
#include "Core/UI/GameMenuUserWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	check(GameMenuUserWidgetClass)
	GameMenuUserWidget = CreateWidget<UGameMenuUserWidget>(GetWorld(), GameMenuUserWidgetClass);
	check(GameMenuUserWidget)
	GameMenuUserWidget->AddToViewport();
	GameMenuUserWidget->SetVisibility(ESlateVisibility::Hidden);

	check(CrosshairWidgetClass)
	CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
	check(CrosshairWidget)
	CrosshairWidget->AddToViewport();

	check(CharacterHUDWidgetClass)
	CharacterHUDWidget = CreateWidget<UCharacterHUDWidget>(GetWorld(), CharacterHUDWidgetClass);
	check(CharacterHUDWidget)
	CharacterHUDWidget->AddToViewport();
}

bool ABaseHUD::ToggleMenu()
{
	if (GameMenuUserWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		GameMenuUserWidget->SetVisibility(ESlateVisibility::Visible);
		CharacterHUDWidget->SetVisibility(ESlateVisibility::Hidden);
		CrosshairWidget->SetVisibility(ESlateVisibility::Hidden);
		return true;
	}

	CharacterHUDWidget->SetVisibility(ESlateVisibility::Visible);
	CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
	GameMenuUserWidget->SetVisibility(ESlateVisibility::Hidden);
	return false;
}

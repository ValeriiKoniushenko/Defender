// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class DEFENDER_API UGameMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnOpenHost();

	UFUNCTION()
	void OnSettings();

	UFUNCTION()
	void OnBackToMenu();

	UFUNCTION()
	void OnBackToDesktop();

protected:
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(meta=(BindWidget))
	UButton* OpenHostButton;

	UPROPERTY(meta=(BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta=(BindWidget))
	UButton* BackToMenuButton;

	UPROPERTY(meta=(BindWidget))
	UButton* BackToDesktopButton;
};

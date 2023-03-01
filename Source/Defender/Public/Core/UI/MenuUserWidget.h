// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Multiplayer/MainGameSession.h"

#include "MenuUserWidget.generated.h"

class UTableWidget;
class UCanvasPanel;
class UEditableText;
class UWidgetSwitcher;
class UButton;
/**
 * 
 */
UCLASS()
class DEFENDER_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnMultiplayer();

	UFUNCTION()
	void OnSettings();

	UFUNCTION()
	void OnExit();

	UFUNCTION()
	void OnBackToMainMenu();

	UFUNCTION()
	void OnLan();

	UFUNCTION()
	void OnLanConnect();

	UFUNCTION()
	void OnOnline();

	UFUNCTION()
	void OnBackToMultiplayerButtonFromLan();

	UFUNCTION()
	void OnUpdateOnlineTable();

protected:
	UFUNCTION()
	void OnFoundSessionResult(TArray<FSearchResult> SearchResults);
	
protected:
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* StartFadeIn;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* GoRightButtons;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* GoLeftButtons;

	// Main Menu
	UPROPERTY(meta=(BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* MultiplayerButton;

	UPROPERTY(meta=(BindWidget))
	UButton* SettingsButton;

	UPROPERTY(meta=(BindWidget))
	UButton* ExitButton;

	// Settings Menu
	UPROPERTY(meta=(BindWidget))
	UButton* BackToMainMenuButton;

	// Multiplayer Menu
	UPROPERTY(Transient, meta=(BindWidget))
	UButton* BackToMainMenuButtonFromMultiplayer;

	UPROPERTY(Transient, meta=(BindWidget))
	UButton* LanButton;

	UPROPERTY(Transient, meta=(BindWidget))
	UButton* OnlineButton;

	// Multiplayer:Lan Menu
	UPROPERTY(Transient, meta=(BindWidget))
	UButton* LanConnectButton;

	UPROPERTY(Transient, meta=(BindWidget))
	UEditableText* LanIP;

	UPROPERTY(Transient, meta=(BindWidget))
	UButton* BackToMultiplayerButtonFromLan;

	// Multiplayer:Online Menu
	UPROPERTY(Transient, meta=(BindWidget))
	UTableWidget* TableWidget;

	UPROPERTY(Transient, meta=(BindWidget))
	UButton* BackToMultiplayerButtonFromOnline;

	UPROPERTY(Transient, meta=(BindWidget))
	UButton* UpdateOnlineTable;
};

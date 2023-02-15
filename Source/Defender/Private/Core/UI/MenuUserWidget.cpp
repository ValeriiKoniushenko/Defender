// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/MenuUserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"

#pragma warning(push)
#pragma warning(disable: 4996)

void UMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(StartGameButton);
	StartGameButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnStartGame);

	check(MultiplayerButton);
	MultiplayerButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnMultiplayer);

	check(SettingsButton);
	SettingsButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnSettings);

	check(ExitButton);
	ExitButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnExit);

	check(BackToMainMenuButton);
	BackToMainMenuButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnBackToMainMenu);

	check(BackToMainMenuButtonFromMultiplayer);
	BackToMainMenuButtonFromMultiplayer->OnClicked.AddDynamic(this, &UMenuUserWidget::OnBackToMainMenu);
	
	check(LanButton);
	LanButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnLan);
	
	check(LanConnectButton);
	LanConnectButton->OnClicked.AddDynamic(this, &UMenuUserWidget::OnLanConnect);
	
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	PlayAnimation(StartFadeIn);
	PlayAnimation(GoRightButtons);
}

void UMenuUserWidget::OnStartGame()
{
	if (GetWorld())
	{
		GetWorld()->ServerTravel("/Game/Defender/Maps/TestMap?listen");
		PlayAnimation(GoLeftButtons);
	}
}

void UMenuUserWidget::OnMultiplayer()
{
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([&]
	{
		PlayAnimation(GoRightButtons);
		MenuSwitcher->SetActiveWidgetIndex(2);
	});

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 1.0f, false);

	PlayAnimation(GoLeftButtons);
}

void UMenuUserWidget::OnSettings()
{
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([&]
	{
		PlayAnimation(GoRightButtons);
		MenuSwitcher->SetActiveWidgetIndex(1);
	});

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 1.0f, false);

	PlayAnimation(GoLeftButtons);
}

void UMenuUserWidget::OnExit()
{
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([&]
	{
		PlayAnimation(GoRightButtons);
		GIsRequestingExit = true;
	});

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 1.0f, false);

	PlayAnimation(GoLeftButtons);
}

void UMenuUserWidget::OnBackToMainMenu()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UMenuUserWidget::OnLan()
{
	
}

void UMenuUserWidget::OnLanConnect()
{
	UGameplayStatics::OpenLevel(GetWorld(),  FName(LanIP->GetText().ToString()));
}

void UMenuUserWidget::OnOnline()
{
	
}

#pragma warning(pop)

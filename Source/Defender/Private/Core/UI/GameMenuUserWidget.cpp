// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UI/GameMenuUserWidget.h"

#include "Components/Button.h"
#include "Core/MainGameModeBase.h"
#include "Core/Multiplayer/MainGameSession.h"
#include "Kismet/GameplayStatics.h"

void UGameMenuUserWidget::SetVisibility(ESlateVisibility InVisibility)
{
	if (InVisibility == ESlateVisibility::Visible)
	{
		PlayAnimation(FadeIn);
	}

	Super::SetVisibility(InVisibility);
}

void UGameMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	check(OpenHostButton);
	OpenHostButton->OnClicked.AddDynamic(this, &ThisClass::OnOpenHost);

	check(SettingsButton);
	SettingsButton->OnClicked.AddDynamic(this, &ThisClass::OnSettings);

	check(BackToMenuButton);
	BackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnBackToMenu);

	check(BackToDesktopButton);
	BackToDesktopButton->OnClicked.AddDynamic(this, &ThisClass::OnBackToDesktop);
}

void UGameMenuUserWidget::OnOpenHost()
{
	AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	check(MainGameModeBase);
	AMainGameSession* MainGameSession = Cast<AMainGameSession>(MainGameModeBase->GameSession);
	check(MainGameSession);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	MainGameSession->HostSession(LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId(), "MySession1");
}

void UGameMenuUserWidget::OnSettings()
{
}

void UGameMenuUserWidget::OnBackToMenu()
{
	if (GetWorld())
	{
		GetWorld()->ServerTravel("/Game/Defender/Maps/MainMenuMap");
	}
}

void UGameMenuUserWidget::OnBackToDesktop()
{
	GIsRequestingExit = true;
}

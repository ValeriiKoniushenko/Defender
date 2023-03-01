// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/MenuUserWidget.h"

#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Core/MainMenuGameModeBase.h"
#include "Core/UI/TableWidget.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

#pragma warning(push)
#pragma warning(disable: 4996)

void UMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(StartGameButton);
	StartGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGame);

	check(MultiplayerButton);
	MultiplayerButton->OnClicked.AddDynamic(this, &ThisClass::OnMultiplayer);

	check(SettingsButton);
	SettingsButton->OnClicked.AddDynamic(this, &ThisClass::OnSettings);

	check(ExitButton);
	ExitButton->OnClicked.AddDynamic(this, &ThisClass::OnExit);

	check(BackToMainMenuButton);
	BackToMainMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnBackToMainMenu);

	check(BackToMainMenuButtonFromMultiplayer);
	BackToMainMenuButtonFromMultiplayer->OnClicked.AddDynamic(this, &ThisClass::OnBackToMainMenu);

	check(LanButton);
	LanButton->OnClicked.AddDynamic(this, &ThisClass::OnLan);

	check(OnlineButton);
	OnlineButton->OnClicked.AddDynamic(this, &ThisClass::OnOnline);

	check(LanConnectButton);
	LanConnectButton->OnClicked.AddDynamic(this, &ThisClass::OnLanConnect);

	check(BackToMultiplayerButtonFromLan);
	BackToMultiplayerButtonFromLan->OnClicked.AddDynamic(this, &ThisClass::OnBackToMultiplayerButtonFromLan);

	check(BackToMultiplayerButtonFromOnline);
	BackToMultiplayerButtonFromOnline->OnClicked.AddDynamic(this, &ThisClass::OnBackToMultiplayerButtonFromLan);

	check(UpdateOnlineTable);
	UpdateOnlineTable->OnClicked.AddDynamic(this, &ThisClass::OnUpdateOnlineTable);

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
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([&]
	{
		PlayAnimation(GoRightButtons);
		MenuSwitcher->SetActiveWidgetIndex(0);
	});

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 1.0f, false);

	PlayAnimation(GoLeftButtons);
}

void UMenuUserWidget::OnLan()
{
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([&]
	{
		PlayAnimation(GoRightButtons);
		MenuSwitcher->SetActiveWidgetIndex(3);
	});

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 1.0f, false);

	PlayAnimation(GoLeftButtons);
}

void UMenuUserWidget::OnLanConnect()
{
	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(LanIP->GetText().ToString(),ETravelType::TRAVEL_Absolute);
	}
	// UGameplayStatics::OpenLevel(GetWorld(), FName(LanIP->GetText().ToString()));
}

void UMenuUserWidget::OnOnline()
{
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([&]
	{
		PlayAnimation(GoRightButtons);
		MenuSwitcher->SetActiveWidgetIndex(4);
	});

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 1.0f, false);

	PlayAnimation(GoLeftButtons);
}

void UMenuUserWidget::OnBackToMultiplayerButtonFromLan()
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

void UMenuUserWidget::OnUpdateOnlineTable()
{
	TableWidget->Clear();
	if (UWorld* World = GetWorld())
	{
		if (AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(World))
		{
			if (AMainMenuGameModeBase* MainMenuGameModeBase = Cast<AMainMenuGameModeBase>(GameModeBase))
			{
				if (AMainGameSession* MainGameSession = Cast<AMainGameSession>(MainMenuGameModeBase->GameSession))
				{
					const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
					MainGameSession->FindSessions(LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId());
					MainGameSession->OnFoundSessionResult.AddDynamic(this, &ThisClass::OnFoundSessionResult);
				}
			}
		}
	}
}

void UMenuUserWidget::OnFoundSessionResult(TArray<FSearchResult> SearchResults)
{
	TableWidget->Clear();
	for (const auto& Session : SearchResults)
	{
		TableWidget->AddRow({ Session.Id, 0, 4, Session.MatchType, Session.Data });
	}
}

#pragma warning(pop)

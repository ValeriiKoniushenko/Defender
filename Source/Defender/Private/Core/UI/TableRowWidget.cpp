#include "Core/UI/TableRowWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Core/MainMenuGameModeBase.h"
#include "Core/Multiplayer/MainGameSession.h"

void UTableRowWidget::OnJoin()
{
	UE_LOG(LogTemp, Warning, TEXT("Join %s"), *IDText->GetText().ToString());
	if (UWorld* World = GetWorld())
	{
		if (AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(World))
		{
			if (AMainMenuGameModeBase* MainMenuGameModeBase = Cast<AMainMenuGameModeBase>(GameModeBase))
			{
				if (AMainGameSession* MainGameSession = Cast<AMainGameSession>(MainMenuGameModeBase->GameSession))
				{
					MainGameSession->JoinSession(SessionData);
				}
			}
		}
	}
}

void UTableRowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Join->OnClicked.AddDynamic(this, &ThisClass::OnJoin);
}

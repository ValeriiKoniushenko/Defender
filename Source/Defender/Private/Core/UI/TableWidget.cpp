#include "Core/UI/TableWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Core/UI/TableRowWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogTableWidget, All, All)

void UTableWidget::AddRow(FOnlineTableRow OnlineTableRow)
{
	if (!RowWidgetClass)
	{
		UE_LOG(LogTableWidget, Fatal, TEXT("RowWidgetClass is empty. Maybe you forget to put a value?"));
		return;
	}

	UUserWidget* Widget = CreateWidget(GetWorld(), RowWidgetClass);
	if (!Widget)
	{
		UE_LOG(LogTableWidget, Fatal, TEXT("Can't create a Widget"));
		return;
	}

	UTableRowWidget* RowWidget = Cast<UTableRowWidget>(Widget);
	if (!RowWidget)
	{
		UE_LOG(LogTableWidget, Fatal, TEXT("Can't cast to a Row Widget"));
	}

	RowWidget->IDText->SetText(FText::FromString(OnlineTableRow.ID));
	RowWidget->PlayersText->SetText(
		FText::FromString(FString::Printf(TEXT("%d/%d"), OnlineTableRow.NowOnlinePlayers, OnlineTableRow.MaxPlayers)));
	RowWidget->ServerDataText->SetText(FText::FromString(OnlineTableRow.ServerData));
	RowWidget->SessionData = OnlineTableRow.Data;
	
	TableContent->AddChild(RowWidget);
}

void UTableWidget::Clear()
{
	TableContent->ClearChildren();
}

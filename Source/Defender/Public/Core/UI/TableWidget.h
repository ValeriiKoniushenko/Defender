#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"

#include "TableWidget.generated.h"

class UTableRowWidget;
class UScrollBox;

USTRUCT()
struct FOnlineTableRow
{
	GENERATED_BODY()

public:
	FString ID;
	int32 NowOnlinePlayers;
	int32 MaxPlayers;
	FString ServerData;
	FOnlineSessionSearchResult Data;
};

UCLASS()
class DEFENDER_API UTableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddRow(FOnlineTableRow OnlineTableRow);
	void Clear();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTableRowWidget> RowWidgetClass;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* TableContent;
};

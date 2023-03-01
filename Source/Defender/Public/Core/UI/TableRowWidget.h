#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"

#include "TableRowWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class DEFENDER_API UTableRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnJoin();

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* IDText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayersText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ServerDataText;

	UPROPERTY(meta=(BindWidget))
	UButton* Join;

	FOnlineSessionSearchResult SessionData;

protected:
	virtual void NativeConstruct() override;
};

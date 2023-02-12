// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "BaseHUD.generated.h"

class UUserWidget;

UCLASS()
class DEFENDER_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	TArray<TSubclassOf<UUserWidget>> Widgets;

private:
	void CreateAllWidgets();
	
private:
	TArray<UUserWidget*> CreatedWidgets;
};

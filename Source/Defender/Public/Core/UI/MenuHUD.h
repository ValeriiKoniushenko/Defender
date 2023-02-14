// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

class UMenuUserWidget;

/**
 * 
 */
UCLASS()
class DEFENDER_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UMenuUserWidget* MenuHUDWidget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	TSubclassOf<UMenuUserWidget> MenuWidgetClass;
};

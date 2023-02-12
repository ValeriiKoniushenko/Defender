// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/BaseHUD.h"
#include "Blueprint/UserWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateAllWidgets();
}

void ABaseHUD::CreateAllWidgets()
{
	for (auto& Widget : Widgets)
	{
		UUserWidget* CreatedWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
		CreatedWidget->AddToViewport();
		CreatedWidgets.Add(CreatedWidget);
	}
}

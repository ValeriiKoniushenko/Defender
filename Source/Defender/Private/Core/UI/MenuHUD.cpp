// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/MenuHUD.h"

#include "Core/UI/MenuUserWidget.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	check(MenuWidgetClass)
	MenuHUDWidget = CreateWidget<UMenuUserWidget>(GetWorld(), MenuWidgetClass);
	check(MenuHUDWidget)
	MenuHUDWidget->AddToViewport();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Pickup/BasePickup.h"
#include "Components/SphereComponent.h"

ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	InteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractSphere"));
	InteractSphere->SetupAttachment(RootComponent);

	bGenerateOverlapEventsDuringLevelStreaming = true;
}

void ABasePickup::Hide()
{
	StaticMeshComponent->SetVisibility(false);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractSphere->SetVisibility(false);
	InteractSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void ABasePickup::Show()
{
	StaticMeshComponent->SetVisibility(true);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	InteractSphere->SetVisibility(true);
	InteractSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ABasePickup::Pickup()
{
	Hide();

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this]
	{
		Show();
	});
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, RespawnTime, false);
}

void ABasePickup::Spawn()
{
	if (FMath::IsNearlyZero(SpawnAfter))
	{
		Show();
		return;
	}

	Hide();
	
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this]
	{
		Show();

		FTimerDelegate TimerCallback;
		TimerCallback.BindLambda([this]
		{
			StopSpawn();
		});
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, VisibleTime, false);
	});
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, SpawnAfter, false);
}

void ABasePickup::StopSpawn()
{
	if (FMath::IsNearlyZero(VisibleTime))
	{
		Show();		
		return;
	}

	Hide();
	Spawn();
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

	Spawn();
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Weapon/BaseWeapon.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::MakeShot()
{
	FHitResult Hit;

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 1000.0f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}
}

void ABaseWeapon::Reload()
{
	const int32 NeededCountOfBullets = Settings.CountOfBulletsInMagazine - Settings.CountOfBullets;
	Settings.CountOfBullets += NeededCountOfBullets;
	Settings.TotalCountOfBullets -= NeededCountOfBullets;
	if (Settings.TotalCountOfBullets < 0)
	{
		Settings.CountOfBullets += Settings.TotalCountOfBullets;
		Settings.TotalCountOfBullets = 0;
	}
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


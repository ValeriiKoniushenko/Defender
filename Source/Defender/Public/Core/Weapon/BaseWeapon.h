// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

USTRUCT()
struct FWeaponSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	int32 CountOfBulletsInMagazine = 16;
	
	UPROPERTY(EditAnywhere)
	int32 CountOfBullets = CountOfBulletsInMagazine;
	
	UPROPERTY(EditAnywhere)
	int32 TotalCountOfBullets = CountOfBulletsInMagazine * 3;

	UPROPERTY(EditAnywhere)
	float BarrelLength = 10.f;
	
	UPROPERTY(EditAnywhere)
	FName WeaponName = "None";

	UPROPERTY(EditAnywhere)
	float BulletSpread = 1.f;

	UPROPERTY(EditAnywhere)
	float FireRate = 30.f; // bullets per second
};

UCLASS()
class DEFENDER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();
	
public:	
	UPROPERTY(EditAnywhere)
	FWeaponSettings Settings;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void MakeShot();

	UFUNCTION(BlueprintCallable)
	void Reload();
	
protected:
	UPROPERTY(EditAnywhere, Category=Collision)
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Visual)
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	
public:	
	virtual void Tick(float DeltaTime) override;
};

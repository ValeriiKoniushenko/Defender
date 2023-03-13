// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class DEFENDER_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	USphereComponent* InteractSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	float SpawnAfter = 0.f; // seconds
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	float RespawnTime = 10.f; // seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	float VisibleTime = 0.f;

	UFUNCTION(BlueprintCallable)
	void Hide();

	UFUNCTION(BlueprintCallable)
	void Show();

	UFUNCTION(BlueprintCallable)
	virtual void Pickup(ABaseCharacter* BaseCharacter);
	
protected:
	void Spawn();
	void StopSpawn();
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};

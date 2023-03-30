#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DEFENDER_API ABasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickUp();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	TSubclassOf<AActor> SpawnedActor;
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)
	UStaticMeshComponent* StaticMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

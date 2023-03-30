#include "Core/Pickup/BasePickUp.h"

#include "Components/StaticMeshComponent.h"

ABasePickUp::ABasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ABasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


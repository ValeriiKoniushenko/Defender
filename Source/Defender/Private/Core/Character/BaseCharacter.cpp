
#include "Core/Character/BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Core/Controllers/BasePlayerController.h"
#include "GameFramework/SpringArmComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	check(SpringArmComponent);
	SpringArmComponent->SetupAttachment(GetMesh());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 140.f));
	SpringArmComponent->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	check(CameraComponent);
	CameraComponent->AttachToComponent(SpringArmComponent, {EAttachmentRule::KeepRelative, false});
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	ABasePlayerController* CurrentController = Cast<ABasePlayerController>(GetController());
	check(CurrentController);
	
	PlayerInputComponent->BindAxis("MoveForward", CurrentController, &ABasePlayerController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", CurrentController, &ABasePlayerController::MoveRight);
	PlayerInputComponent->BindAxis("LookAround", CurrentController, &ABasePlayerController::LookAround);
	PlayerInputComponent->BindAxis("LookUp", CurrentController, &ABasePlayerController::LookUp);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, CurrentController, &ABasePlayerController::Jump);
	PlayerInputComponent->BindAction("MainAction", IE_Pressed, CurrentController, &ABasePlayerController::MainAction);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, CurrentController, &ABasePlayerController::SecondaryAction);
}


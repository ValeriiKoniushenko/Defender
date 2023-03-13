#include "Core/Controllers/BasePlayerController.h"

#include "Core/Character/BaseCharacter.h"
#include "GameFramework/Character.h"

void ABasePlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	ABaseCharacter* CharacterBase = Cast<ABaseCharacter>(P);
	if (CharacterBase)
	{
		CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
	}
}

void ABasePlayerController::MoveForward(float Value)
{
	ACharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter)
	{
		CurrentCharacter->AddMovementInput(CurrentCharacter->GetActorForwardVector(), Value);
	}
}

void ABasePlayerController::MoveRight(float Value)
{
	ACharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter)
	{
		CurrentCharacter->AddMovementInput(CurrentCharacter->GetActorRightVector(), Value);
	}
}

void ABasePlayerController::LookAround(float Value)
{
	ACharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter)
	{
		CurrentCharacter->AddControllerYawInput(Value);
	}
}

void ABasePlayerController::LookUp(float Value)
{
	ACharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter)
	{
		CurrentCharacter->AddControllerPitchInput(Value);
	}
}

void ABasePlayerController::Jump()
{
	ABaseCharacter* CurrentCharacter = Cast<ABaseCharacter>(GetCharacter());
	if (CurrentCharacter)
	{
		CurrentCharacter->Jump();
	}
}

void ABasePlayerController::MainAction()
{
	ACharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter)
	{
		
	}
}

void ABasePlayerController::SecondaryAction()
{
	ACharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter)
	{
		
	}
}

void ABasePlayerController::StartCrouch()
{
	ACharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter)
	{
		CurrentCharacter->Crouch();
	}
}

void ABasePlayerController::EndCrouch()
{
	ACharacter* CurrentCharacter = GetCharacter();
	if (CurrentCharacter)
	{
		CurrentCharacter->UnCrouch();
	}
}

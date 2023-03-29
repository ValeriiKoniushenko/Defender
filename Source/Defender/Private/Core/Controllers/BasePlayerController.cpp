#include "Core/Controllers/BasePlayerController.h"

#include "Core/Character/BaseCharacter.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogABasePlayerController, All, All)

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

void ABasePlayerController::StartRun()
{
	ActivateCharacterAbilityByTag("character.moving.run");
}

void ABasePlayerController::EndRun()
{
	ActivateCharacterAbilityByTag("character.moving.jog");
}

void ABasePlayerController::StartWalk()
{
	ActivateCharacterAbilityByTag("character.moving.walk");
}

void ABasePlayerController::EndWalk()
{
	ActivateCharacterAbilityByTag("character.moving.jog");
}

void ABasePlayerController::ActivateCharacterAbilityByTag(FName TagName)
{
	if (const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter()))
	{
		FGameplayTagContainer GameplayTagContainer;
		GameplayTagContainer.AddTag(FGameplayTag::RequestGameplayTag(TagName));
		
		if (!BaseCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(GameplayTagContainer))
		{
			UE_LOG(LogABasePlayerController, Error, TEXT("Can't activate ability: %s - maybe you forget to add this ability to ASC in a class."), *GameplayTagContainer.GetByIndex(0).ToString());
		}
	}
}

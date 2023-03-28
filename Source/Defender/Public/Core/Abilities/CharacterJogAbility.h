#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharacterJogAbility.generated.h"

UCLASS()
class DEFENDER_API UCharacterJogAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UCharacterJogAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Effects)
	TSubclassOf<UGameplayEffect> JogEffect;
};

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CharacterRunAbility.generated.h"

/**
 * 
 */
UCLASS()
class DEFENDER_API UCharacterRunAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UCharacterRunAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Effects)
	TSubclassOf<UGameplayEffect> RunEffect;
};

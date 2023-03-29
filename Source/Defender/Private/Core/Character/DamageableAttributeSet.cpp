#include "Core/Character/DamageableAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UDamageableAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDamageableAttributeSet, Health, OldHealth);
}

void UDamageableAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDamageableAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

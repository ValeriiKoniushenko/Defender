#pragma once

#include "AbilitySystemInterface.h"
#include "Core/Character/BaseCharacterAttributeSet.h"
#include "CoreMinimal.h"
#include "Core/Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Interfaces/OnlineSessionInterface.h"
// #include "Engine/DataTable.h"

#include "BaseCharacter.generated.h"

class ABaseWeapon;
class UAbilitySystemComponent;
class UAnimMontage;
class UCameraComponent;
class USpringArmComponent;
class UWeaponInventoryComponent;

UCLASS()
class DEFENDER_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void SpawnWeapon(TSubclassOf<ABaseWeapon> WeaponClass);
	virtual void AddWeaponToInventory(TSubclassOf<ABaseWeapon> WeaponClass, const FWeaponSettings& WeaponSettings);

protected:
	void OnMaxWalkSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData);

	virtual void BeginPlay() override;

	virtual void ToggleGameMenu();

	UFUNCTION(BlueprintCallable)
	float GetSpeed() const;

	void InitializeAttributes();

	void GiveAbilities();

	UFUNCTION(BlueprintCallable)
	float GetDirection() const;

	// UFUNCTION(BlueprintCallable)
	// void LoadFromDataTable();

	UFUNCTION(BlueprintCallable)
	bool ActivateAbilitiesByTag(FGameplayTagContainer GameplayTagContainer, bool bAllowedRemoteActivation);

	UFUNCTION()
	void UpdateStatusBar();

protected:
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	// UDataTable* ConfigTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	ABaseWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	UWeaponInventoryComponent* WeaponInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	UAnimMontage* JumpFromStand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	UAnimMontage* JumpFromJog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Abilities")
	UBaseCharacterAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
};

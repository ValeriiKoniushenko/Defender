#pragma once

#include "AbilitySystemInterface.h"
#include "Core/Character/BaseCharacterAttributeSet.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"

#include "BaseCharacter.generated.h"

class UAbilitySystemComponent;
class UAnimMontage;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DEFENDER_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable)
	float GetDirection() const;

	// UFUNCTION(BlueprintCallable)
	// void LoadFromDataTable();

	UFUNCTION()
	void UpdateStatusBar();
	
protected:
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	// UDataTable* ConfigTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	UBaseCharacterAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	UAnimMontage* JumpFromStand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	UAnimMontage* JumpFromJog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
};

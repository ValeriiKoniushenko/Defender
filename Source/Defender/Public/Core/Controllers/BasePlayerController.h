#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEFENDER_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void AcknowledgePossession(APawn* P) override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookAround(float Value);
	void LookUp(float Value);
	void Jump();
	void MainAction();
	void SecondaryAction();
	void StartCrouch();
	void EndCrouch();
};

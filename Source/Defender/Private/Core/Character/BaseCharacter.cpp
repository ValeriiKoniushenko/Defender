#include "Core/Character/BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/ProgressBar.h"
#include "Core/Controllers/BasePlayerController.h"
#include "Core/Inventory/WeaponInventoryComponent.h"
#include "Core/Pickup/BasePickUp.h"
#include "Core/UI/BaseHUD.h"
#include "Core/UI/CharacterHUDWidget.h"
#include "Core/UI/GameMenuUserWidget.h"
#include "Core/Weapon/BaseWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
	
DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

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

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbiltySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UBaseCharacterAttributeSet>(TEXT("Attribute Set"));

	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	// ConfigTable = CreateDefaultSubobject<UDataTable>(TEXT("Config"));

	WeaponInventoryComponent = CreateDefaultSubobject<UWeaponInventoryComponent>(TEXT("WeaponInventoryComponent"));

	bReplicates = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxWalkSpeedAttribute()).
	                        AddUObject(this, &ThisClass::OnMaxWalkSpeedChanged);
	// LoadFromDataTable();
}

void ABaseCharacter::ToggleGameMenu()
{
	ABaseHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ABaseHUD>();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = HUD->ToggleMenu();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStatusBar();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();

	SetOwner(NewController);
}

float ABaseCharacter::GetSpeed() const
{
	return GetVelocity().Size2D();
}

void ABaseCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			DefaultAttributeEffect, 1, EffectContextHandle);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(
				*SpecHandle.Data.Get());
		}
	}
}

void ABaseCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
		}
	}
}

float ABaseCharacter::GetDirection() const
{
	FVector Velocity = GetMovementComponent()->Velocity;
	FVector ForwardVector = GetActorForwardVector();
	Velocity.Normalize();

	float ACos = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Velocity, ForwardVector)));
	float Sign = FMath::Sign(FVector::CrossProduct(Velocity, ForwardVector).Z);

	return ACos * Sign;
}

/*void ABaseCharacter::LoadFromDataTable()
{
	if (!ConfigTable)
	{
		UE_LOG(LogBaseCharacter, Error, TEXT("ConfigTable is not initialized"));
		return;
	}

	for (auto Row : ConfigTable->GetRowMap())
	{
		const FAttributeMetaData* Data = reinterpret_cast<FAttributeMetaData*>(Row.Value);
		if (Row.Key == "BaseCharacterAttributeSet.Health")
		{
			AttributeSet->Health.SetBaseValue(Data->BaseValue);
			AttributeSet->Health.SetCurrentValue(Data->BaseValue);
		}
		else if (Row.Key == "BaseCharacterAttributeSet.Stamina")
		{
			AttributeSet->Stamina.SetBaseValue(Data->BaseValue);
			AttributeSet->Stamina.SetCurrentValue(Data->BaseValue);
		}
	}
}*/

void ABaseCharacter::UpdateStatusBar()
{
	ABaseHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ABaseHUD>();
	check(HUD);
	HUD->CharacterHUDWidget->HealthProgressBar->SetPercent(
		AttributeSet->Health.GetCurrentValue() / AttributeSet->Health.GetBaseValue());
	HUD->CharacterHUDWidget->StaminaProgressBar->SetPercent(
		AttributeSet->Stamina.GetCurrentValue() / AttributeSet->Stamina.GetBaseValue());
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
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, CurrentController,
	                                 &ABasePlayerController::SecondaryAction);
	PlayerInputComponent->BindAction("ToggleGameMenu", IE_Pressed, this, &ThisClass::ToggleGameMenu);
	PlayerInputComponent->BindAction("Run", IE_Pressed, CurrentController, &ABasePlayerController::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, CurrentController, &ABasePlayerController::EndRun);
	PlayerInputComponent->BindAction("Walk", IE_Pressed, CurrentController, &ABasePlayerController::StartWalk);
	PlayerInputComponent->BindAction("Walk", IE_Released, CurrentController, &ABasePlayerController::EndWalk);
}

void ABaseCharacter::Jump()
{
	Super::Jump();
	if (!GetMovementComponent()->IsFalling())
	{
		if (FMath::IsNearlyZero(GetSpeed()))
		{
			check(JumpFromStand);
			PlayAnimMontage(JumpFromStand);
		}
		else
		{
			check(JumpFromJog);
			PlayAnimMontage(JumpFromJog);
		}
	}
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (ABasePickUp* BasePickUp = Cast<ABasePickUp>(OtherActor))
	{
		if (UWorld* World = GetWorld())
		{
			if (BasePickUp->SpawnedActor)
			{
				AActor* SpawnedActor = World->SpawnActor(BasePickUp->SpawnedActor);
				if (!SpawnedActor->AttachToComponent(GetMesh(), { EAttachmentRule::SnapToTarget, false }, HandSocket))
				{
					UE_LOG(LogBaseCharacter, Error, TEXT("Can't attach a picked up actor to the hand socket"));
				}
			}
			else
			{
				UE_LOG(LogBaseCharacter, Error, TEXT("Can't create a picked up actor. It has no a specified class to spawn 'SpawnedActor'"));
			}
		}
	}
}

void ABaseCharacter::OnMaxWalkSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	GetCharacterMovement()->MaxWalkSpeed = OnAttributeChangeData.NewValue;
}

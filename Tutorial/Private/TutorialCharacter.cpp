// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCharacter.h"
#include "TutorialAnimInstance.h"
#include "TutorialWeapon.h"
#include "TutorialCharacterStatComponent.h"
#include "TutorialCharacterWidget.h"
#include "TutorialAIController.h"
#include "TutorialGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Components/WidgetComponent.h"
#include "TutorialCharacterSetting.h"

// Sets default values
ATutorialCharacter::ATutorialCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArmLengthTo = 0.0f;
	ArmRotationTo = FRotator::ZeroRotator;
	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;

	IsComboInputOn = false;
	CanNextCombo = false;
	MaxCombo = 4;
	CurrentCombo = 0;
	IsAttacking = false;

	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	WeaponSocket = FName(TEXT("hand_rSocket"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterStat = CreateDefaultSubobject<UTutorialCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	HPBarWidget->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));

	CurrentCameraMode = ECameraMode::TopView;
	
	DirectionToMove = FVector::ZeroVector;
	GetCharacterMovement()->JumpZVelocity = 800.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TCharacter"));

	AIControllerClass = ATutorialAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void ATutorialCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultWeaponClass)
	{
		auto SpawnedWeapon = GetWorld()->SpawnActor<ATutorialWeapon>(DefaultWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		SpawnedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		//Set Skeleton Socket position and rotation instead of Weapon
	}

	if (!IsPlayerControlled())
	{
		auto DefaultSetting = GetDefault<UTutorialCharacterSetting>();
		int32 RandIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
		CharacterAssetToLoad = DefaultSetting->CharacterAssets[RandIndex];

		auto TGameInstance = Cast<UTutorialGameInstance>(GetGameInstance());
		if (TGameInstance != nullptr)
		{
			//
			AssetStreamingHandle = TGameInstance->StreamableManager.RequestAsyncLoad(
				CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &ATutorialCharacter::OnAssetLoadCompleted));
		}
	}
}

// Called every frame
void ATutorialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentCameraMode)
	{
	case ECameraMode::TopView:
		SpringArm->SetRelativeRotation(FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed));
		break;
	}
}

void ATutorialCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TAnim = Cast<UTutorialAnimInstance>(GetMesh()->GetAnimInstance());
	CHECK(TAnim !=nullptr);

	TAnim->OnMontageEnded.AddDynamic(this, &ATutorialCharacter::OnAttackMontageEnded);
	TAnim->OnAttackHitCheck.AddUObject(this, &ATutorialCharacter::AttackCheck);
	TAnim->OnNextAttackCheck.AddLambda([this]() -> void {
		LOG(Warning, TEXT("OnNextAttackCheck"));
		CanNextCombo = false;

		if (IsComboInputOn)
		{
			AttackStartComboState();
			TAnim->JumpToAttackMontageSection(CurrentCombo);
		}
		});

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {

		LOG(Warning, TEXT("HP ZERO"));
		TAnim->SetDeadAnim();
		SetActorEnableCollision(false);
		});
	
	HPBarWidget->InitWidget();
	auto CharacterWidget = Cast<UTutorialCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	CHECK(CharacterWidget != nullptr);
	if (CharacterWidget != nullptr)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
}

void ATutorialCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsPlayerControlled())
	{
		SetCameraMode(CurrentCameraMode);
		SetPlayer();
	}
	else
	{
		SetNonPlayer();
	}
}

// Called to bind functionality to input
void ATutorialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATutorialCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	LOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	CharacterStat->SetDamage(FinalDamage);

	return FinalDamage;
}

void ATutorialCharacter::Move(const FVector2D& Vector)
{
	switch (CurrentCameraMode)
	{
	// Get Front from 'this rotation'
	case ECameraMode::BackView:
		//EAxis::Value == Unreal XYZ Vector, Vector.Value == Input XY Vector 
		//Forward
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), Vector.Y);
		//Right	
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), Vector.X);
		break;
	// Get Front from 'this movement', then set rotation
	case ECameraMode::TopView:
		DirectionToMove.X = Vector.Y;
		DirectionToMove.Y = Vector.X;
		//Set Control Rotation >> bUseControllerDesiredRotation >> Pawn rotates
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		AddMovementInput(DirectionToMove);
	}
}

void ATutorialCharacter::Look(const FVector2D& Vector)
{
	switch (CurrentCameraMode)
	{
	case ECameraMode::BackView:
		AddControllerPitchInput(Vector.Y);
		AddControllerYawInput(Vector.X);
		break;
	}
}

void ATutorialCharacter::CustomJump()
{
}

void ATutorialCharacter::CustomStopJump()
{
}


void ATutorialCharacter::ChangeCameraMode()
{
	switch (CurrentCameraMode)
	{
	case ECameraMode::BackView:
		//Top View Controller Rotation should follow Pawn Rotation
		GetController()->SetControlRotation(GetActorRotation());
		SetCameraMode(ECameraMode::TopView);
		break;
	case ECameraMode::TopView:
		//To make transition smoothly from Top View to Back View
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SetCameraMode(ECameraMode::BackView);
		break;
	}
}

void ATutorialCharacter::Attack()
{
	if (IsAttacking)
	{
		CHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		CHECK(CurrentCombo == 0);
		AttackStartComboState();
		TAnim->PlayAttackMontage();
		TAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void ATutorialCharacter::SetBackViewCamera()
{
	ArmLengthTo = 450.0f;
	//UsePawnControlRotation: SpringArm match its rotation to the Player Controller's control rotation. 
	//For SpringArm's desired rotation
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;

	//UseControllerRotationYaw: Pawn follows Controller's rotation
	bUseControllerRotationYaw = false;
	//OrientRotationToMovement: Rotates with Movement(priority)
	//UseControllerDesiredRotation: Rotates with Controller
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void ATutorialCharacter::SetTopViewCamera()
{
	ArmLengthTo = 800.0f;
	ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void ATutorialCharacter::SetCameraMode(ECameraMode NewCameraMode)
{
	CurrentCameraMode = NewCameraMode;

	switch (CurrentCameraMode)
	{
	case ECameraMode::BackView:
		SetBackViewCamera();
		break;
	case ECameraMode::TopView:
		SetTopViewCamera();
		break;
	}
}

void ATutorialCharacter::SetPlayer()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ATutorialCharacter::SetNonPlayer()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}


void ATutorialCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	CHECK(IsAttacking);
	CHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
	OnAttackEnd.Broadcast();
}

void ATutorialCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ATutorialCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void ATutorialCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG
	
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapusuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,			//Location
		HalfHeight,		//Half Length of Capsule
		AttackRadius,	
		CapusuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif
	if (bResult)
	{
		if (HitResult.GetActor())
		{
			LOG(Warning, TEXT("Hit Actor Name : %s"), *HitResult.GetActor()->GetName());

			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
		}
	}
}

void ATutorialCharacter::OnAssetLoadCompleted()
{
	AssetStreamingHandle->ReleaseHandle();
	TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(CharacterAssetToLoad);
	if (LoadedAssetPath.IsValid())
	{
		GetMesh()->SetSkeletalMesh(LoadedAssetPath.Get());
	}
}

bool ATutorialCharacter::CanSetWeapon()
{
	return (CurrentWeapon == nullptr);
}

void ATutorialCharacter::SetWeapon(ATutorialWeapon* NewWeapon)
{
	CHECK(NewWeapon != nullptr && CurrentWeapon == nullptr);

	if (NewWeapon != nullptr)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

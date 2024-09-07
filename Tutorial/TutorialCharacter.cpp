// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TutorialAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

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

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	CurrentCameraMode = ECameraMode::TopView;
	SetCameraMode(CurrentCameraMode);
	
	DirectionToMove = FVector::ZeroVector;
	GetCharacterMovement()->JumpZVelocity = 800.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TCharacter"));
}

// Called when the game starts or when spawned
void ATutorialCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	CHECK(nullptr != TAnim);

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

	if (FinalDamage > 0.0f)
	{
		TAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	}

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

void ATutorialCharacter::BackViewCamera()
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

void ATutorialCharacter::TopViewCamera()
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
		BackViewCamera();
		break;
	case ECameraMode::TopView:
		TopViewCamera();
		break;
	}
}

void ATutorialCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	CHECK(IsAttacking);
	CHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
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
			HitResult.GetActor()->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}

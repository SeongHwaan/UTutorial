// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "TutorialCharacter.generated.h"

UCLASS()
class TUTORIAL_API ATutorialCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutorialCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class ECameraMode
	{
		BackView,
		TopView
	};

public:	
	ECameraMode CurrentCameraMode;
	FVector DirectionToMove;

	float ArmLengthTo;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed;
	float ArmRotationSpeed;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Move(const FVector2D& Vector);
	void Look(const FVector2D& Vector);
	void CustomJump();
	void CustomStopJump();
	void ChangeCameraMode();
	void Attack();

	void BackViewCamera();
	void TopViewCamera();
	void SetCameraMode(ECameraMode NewCameraMode);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	FName WeaponSocket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ATutorialWeapon> DefaultWeaponClass;

	bool CanSetWeapon();
	void SetWeapon(class ATutorialWeapon* NewWeapon);
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class ATutorialWeapon> CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UTutorialCharacterStatComponent> CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UWidgetComponent> HPBarWidget;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float AttackRadius;
	
	UPROPERTY()
	TObjectPtr<class UTutorialAnimInstance> TAnim;
};

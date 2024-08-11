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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FVector2D& Vector);
	void Jump(const FInputActionValue& Value);
	void Look(const FVector2D& Vector);

	void BackViewCamera();
	void TopViewCamera();
	void SetCameraMode(ECameraMode NewCameraMode);
	void ChangeCameraMode();

	ECameraMode CurrentCameraMode;
	FVector DirectionToMove;	

	float ArmLengthTo;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed;
	float ArmRotationSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;
};

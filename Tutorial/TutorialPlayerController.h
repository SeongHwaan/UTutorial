// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TutorialPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ATutorialPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;	//Possess is deprecated
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputMappingContext> DefaultContext;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputAction> MoveAction;


	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputAction> JumpAction;


	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputAction> LookAction;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TutorialCharacter.h"
#include "TutorialPlayerController.generated.h"

UCLASS()
class TUTORIAL_API ATutorialPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATutorialPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;	//Possess is deprecated
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	class UTutorialHUDWidget* GetHUDWidget() const;
	void NPCKill(class ATutorialCharacter* KilledNPC) const;
	void AddGameScore() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UTutorialHUDWidget> HUDWidgetClass;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();
	void ChangeCameraMode();
	void Attack();

private:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputMappingContext> DefaultContext;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputAction> CameraChangeAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY()
	TObjectPtr<ATutorialCharacter> TCharacter;

	UPROPERTY()
	TObjectPtr<class UTutorialHUDWidget> HUDWidget;

	UPROPERTY()
	TObjectPtr<class ATutorialPlayerState> TPlayerState;
};

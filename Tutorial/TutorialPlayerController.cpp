// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TutorialCharacter.h"


ATutorialPlayerController::ATutorialPlayerController()
{
	//Using character member here makes NULL problem
}

void ATutorialPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LOG_S(Warning);
}

void ATutorialPlayerController::OnPossess(APawn* aPawn)
{
	LOG_S(Warning);
	Super::OnPossess(aPawn);
}


// Called when the game starts or when spawned
void ATutorialPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TCharacter = Cast<ATutorialCharacter>(GetCharacter());

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		//SubSystem->ClearAllMappings();
		SubSystem->AddMappingContext(DefaultContext, 0);
	}
}

void ATutorialPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATutorialPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATutorialPlayerController::Look);
		EnhancedInputComponent->BindAction(CameraChangeAction, ETriggerEvent::Started, this, &ATutorialPlayerController::ChangeCameraMode);
	}
}

void ATutorialPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	TCharacter->Move(MovementVector);
}

void ATutorialPlayerController::Jump(const FInputActionValue& Value)
{

}

void ATutorialPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D	LookAxisVector = Value.Get<FVector2D>();
	TCharacter->Look(LookAxisVector);
}

void ATutorialPlayerController::ChangeCameraMode()
{
	TCharacter->ChangeCameraMode();
}

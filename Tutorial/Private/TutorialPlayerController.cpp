// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TutorialCharacter.h"
#include "TutorialHUDWidget.h"
#include "TutorialPlayerState.h"
#include "TutorialCharacter.h"
#include "TutorialGamePlayWidget.h"
#include "TutorialResultWidget.h"
#include "TutorialGameStateBase.h"
#include "Kismet/GameplayStatics.h"

ATutorialPlayerController::ATutorialPlayerController()
{
	//Using character member here makes NULL problem
}

void ATutorialPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATutorialPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}


// Called when the game starts or when spawned
void ATutorialPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	ChangeInputMode(true);

	TCharacter = Cast<ATutorialCharacter>(GetCharacter());

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		//SubSystem->ClearAllMappings();
		SubSystem->AddMappingContext(DefaultContext, 0);
	}

	HUDWidget = CreateWidget<UTutorialHUDWidget>(this, HUDWidgetClass);
	CHECK(HUDWidget != nullptr);
	HUDWidget->AddToViewport();

	ResultWidget = CreateWidget<UTutorialResultWidget>(this, ResultWidgetClass);
	CHECK(ResultWidget != nullptr);

	TPlayerState = Cast<ATutorialPlayerState>(PlayerState);
	CHECK(TPlayerState != nullptr);
	HUDWidget->BindPlayerState(TPlayerState);
	TPlayerState->OnPlayerStateChanged.Broadcast();

	ChangeInputMode(true);
}

void ATutorialPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATutorialPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATutorialPlayerController::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATutorialPlayerController::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATutorialPlayerController::StopJump);
		EnhancedInputComponent->BindAction(CameraChangeAction, ETriggerEvent::Started, this, &ATutorialPlayerController::ChangeCameraMode);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ATutorialPlayerController::Attack);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ATutorialPlayerController::Pause);
	}
}

UTutorialHUDWidget* ATutorialPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void ATutorialPlayerController::NPCKill(ATutorialCharacter* KilledNPC) const
{
	TPlayerState->AddExp(KilledNPC->GetExp());
}

void ATutorialPlayerController::AddGameScore() const
{
	TPlayerState->AddGameScore();
}

void ATutorialPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	TCharacter->Move(MovementVector);
}

void ATutorialPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D	LookAxisVector = Value.Get<FVector2D>();
	TCharacter->Look(LookAxisVector);
}

void ATutorialPlayerController::StartJump()
{
	TCharacter->Jump();
}

void ATutorialPlayerController::StopJump()
{
	TCharacter->StopJumping();
}

void ATutorialPlayerController::ChangeCameraMode()
{
	TCharacter->ChangeCameraMode();
}

void ATutorialPlayerController::Attack()
{
	TCharacter->Attack();
}

void ATutorialPlayerController::Pause()
{
	MenuWidget = CreateWidget<UTutorialGamePlayWidget>(this, MenuWidgetClass);
	CHECK(MenuWidget != nullptr);
	//ZOrder: To put Widget above Game 
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}

void ATutorialPlayerController::ShowResultUI()
{
	auto TGameState = Cast<ATutorialGameStateBase>(UGameplayStatics::GetGameState(this));
	CHECK(TGameState != nullptr);
	ResultWidget->BindGameState(TGameState);

	ResultWidget->AddToViewport();
	ChangeInputMode(false);
}

void ATutorialPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

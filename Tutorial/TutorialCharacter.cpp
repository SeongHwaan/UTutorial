// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATutorialCharacter::ATutorialCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
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
}

// Called to bind functionality to input
void ATutorialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATutorialCharacter::Move(const FVector2D& Vector)
{
	AddMovementInput(GetActorForwardVector(), Vector.Y);
	AddMovementInput(GetActorRightVector(), Vector.X);
}

void ATutorialCharacter::Jump(const FInputActionValue& Value)
{

}

void ATutorialCharacter::Look(const FInputActionValue& Value)
{

}


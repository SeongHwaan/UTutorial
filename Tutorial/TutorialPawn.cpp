// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialPawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATutorialPawn::ATutorialPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

// Called when the game starts or when spawned
void ATutorialPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATutorialPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATutorialPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATutorialPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LOG_S(Warning);
}

void ATutorialPawn::PossessedBy(AController* NewController)
{
	LOG_S(Warning);
	Super::PossessedBy(NewController);
}


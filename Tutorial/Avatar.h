// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class UInputAction;
class UInputMappingContext;


UCLASS()
class TUTORIAL_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category = AvatarInput)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = AvatarInput)
	TObjectPtr<UInputMappingContext> DefaultContext;

	void Move();

};

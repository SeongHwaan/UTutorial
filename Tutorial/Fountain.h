// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Fountain.generated.h"


UCLASS()
class TUTORIAL_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Water;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPointLightComponent> Light;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UParticleSystemComponent> Splash;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent> Rotation;


private:
	UPROPERTY(EditAnywhere, Category = Start, Meta = (AllowPrivateAccess = true))
	float RotateSpeed;
};

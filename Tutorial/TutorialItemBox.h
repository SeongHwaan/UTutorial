// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/Actor.h"
#include "TutorialItemBox.generated.h"

UCLASS()
class TUTORIAL_API ATutorialItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, Category = "Box")
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = "Box")
	TObjectPtr<UStaticMeshComponent> Box;

	UPROPERTY(EditAnywhere, Category = "Box")
	TSubclassOf<class ATutorialWeapon> WeaponItemClass;

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	TObjectPtr<class UParticleSystemComponent> Effect;


private:

	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);


};

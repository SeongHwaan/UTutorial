// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/Actor.h"
#include "TutorialSection.generated.h"

UCLASS()
class TUTORIAL_API ATutorialSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialSection();
	
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	enum class ESectionState : uint8
	{
		READY = 0,
		BATTLE,
		COMPLETE
	};

	void SetState(ESectionState NewState);
	ESectionState CurrentState;

	void OperateGates(bool bOpen = true);

	void OnNPCSpawn();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", Meta = (AllowPrivateAccess = true))
	TArray<UStaticMeshComponent*> GateMeshes;

	UPROPERTY(EditDefaultsOnly, Category = "Trigger", Meta = (AllowPrivateAccess = true))
	TArray<UBoxComponent*> GateTriggers;

	UPROPERTY(EditDefaultsOnly, Category = "Trigger", Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(EditAnywhere, Category = "State", Meta = (AllowPrivateAccess = true))
	bool bNoBattle;

	UPROPERTY(EditAnywhere, Category = "Spawn", Meta = (AllowPrivateAccess = true))
	float EnemySpawnTime;

	UPROPERTY(EditAnywhere, Category = "Spawn", Meta = (AllowPrivateAccess = true))
	float ItemBoxSpawnTime;

	FTimerHandle SpawnNPCTimerHandle = {};
	FTimerHandle SpawnItemBoxTimerHandle = {};


	UFUNCTION()
	void OnTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnGateTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class ATutorialItemBox> ItemBoxClass;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class ATutorialCharacter> CharacterClass;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class ATutorialSection> SectionClass;
};

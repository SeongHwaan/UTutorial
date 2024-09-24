// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "TutorialAIController.h"
#include "TutorialCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto TCharacter = Cast<ATutorialCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (TCharacter == nullptr)
		return EBTNodeResult::Failed;

	auto Target = Cast<ATutorialCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATutorialAIController::TargetKey));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - TCharacter->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	TCharacter->SetActorRotation(FMath::RInterpTo(TCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
	LOG(Warning, TEXT("TEST1"));

	return EBTNodeResult::Succeeded;
}

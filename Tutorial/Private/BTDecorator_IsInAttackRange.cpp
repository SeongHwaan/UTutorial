// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "TutorialAIController.h"
#include "TutorialCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	//Cast ATutorialCharacter for using GetFinalAttackRange() method
	auto ControllingPawn = Cast<ATutorialCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return false;

	auto Target = Cast<ATutorialCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATutorialAIController::TargetKey));
	if (Target == nullptr)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= ControllingPawn->GetFinalAttackRange());
	return bResult;
}

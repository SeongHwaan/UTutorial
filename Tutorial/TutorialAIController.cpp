// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ATutorialAIController::HomePosKey(TEXT("HomePos"));
const FName ATutorialAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ATutorialAIController::TargetKey(TEXT("Target"));


ATutorialAIController::ATutorialAIController()
{
	BlackboardComp = Blackboard;
	//RepeatInterval = 3.0f;
}

//If PlayerController possesses the pawn, the PlayerController will not have control until the AIController releases it.
void ATutorialAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ATutorialAIController::OnRepeatTimer, RepeatInterval, true);

	if (UseBlackboard(BBAsset,BlackboardComp))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			LOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}

void ATutorialAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

//void ATutorialAIController::OnRepeatTimer()
//{
//	auto CurrentPawn = GetPawn();
//	CHECK(CurrentPawn != nullptr);
//
//	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//	FNavLocation NextLocation;
//
//	if (NavSystem != nullptr)
//	{
//		if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
//		{
//			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
//			LOG(Warning, TEXT("Next Location: %s"), *NextLocation.Location.ToString());
//		}
//	}
//}

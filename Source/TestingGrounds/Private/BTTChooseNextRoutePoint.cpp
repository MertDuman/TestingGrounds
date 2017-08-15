// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTChooseNextRoutePoint.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTChooseNextRoutePoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	// Get the patrol points from a PatrolRouteComponent
	UPatrolRouteComponent* PatrolRouteComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRouteComponent>();
	if (!ensure(PatrolRouteComponent)) { return EBTNodeResult::Failed; }
	TArray<ATargetPoint*> PatrolPoints = PatrolRouteComponent->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) { return EBTNodeResult::Failed; }

	// Set next patrol point
	int32 CurrentIndex = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	ATargetPoint* PatrolPoint = PatrolPoints[CurrentIndex];
	Blackboard->SetValueAsObject(PatrolPointKey.SelectedKeyName, PatrolPoint);

	// Cycle the index by 1
	int32 CycledValue = (++CurrentIndex) % PatrolPoints.Num();;
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, CycledValue);

	return EBTNodeResult::Succeeded;
}



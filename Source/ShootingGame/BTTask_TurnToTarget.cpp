// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include"ABAIController.h"
#include"ABMonster.h"
#include"ABCharacter.h"
#include"BehaviorTree/BlackboardComponent.h"
UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto ABMonster = Cast<AABMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ABMonster)
		return EBTNodeResult::Failed;
	auto Target = Cast<AABCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::TargetKey));
	if(nullptr==Target)
		return EBTNodeResult::Failed;
	FVector LookVector = Target->GetActorLocation() - ABMonster->GetActorLocation();
	LookVector.Z = 0.f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	ABMonster->SetActorRotation(FMath::RInterpTo(ABMonster->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.f));


	return EBTNodeResult::Succeeded;
}


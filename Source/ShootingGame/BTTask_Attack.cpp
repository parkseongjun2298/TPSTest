// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include"ABAIController.h"
#include"ABMonster.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(Ownercomp, NodeMemory);
	
	
	auto ABMonster = Cast<AABMonster>(Ownercomp.GetAIOwner()->GetPawn());
	if (nullptr == ABMonster)
		return EBTNodeResult::Failed;
	ABMonster->Attack();
	IsAttaking = true;
	ABMonster->OnAttackEnd.AddLambda([this]()->void {

		IsAttaking = false;

		
		});
	
	
	
	return EBTNodeResult::InProgress;
	


}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(Ownercomp, NodeMemory, DeltaSeconds);


	auto ABMonster = Cast<AABMonster>(Ownercomp.GetAIOwner()->GetPawn());
	if (nullptr == ABMonster)
		return;

	if (!IsAttaking)
	{
		FinishLatentTask(Ownercomp, EBTNodeResult::Succeeded);
		ABMonster->bAttackMode = false;
	}
}

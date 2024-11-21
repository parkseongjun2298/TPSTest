// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Attack();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& Ownercomp, uint8* NodeMemory, float DeltaSeconds)override;


private:
	bool IsAttaking = false;
};

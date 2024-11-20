// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "ABAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API AABAIController : public AAIController
{
	GENERATED_BODY()

public:
	AABAIController();
	virtual void OnPossess(APawn* InPawn)override;
	virtual void OnUnPossess()override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	UPROPERTY(VisibleDefaultsOnly, Category = AI)
	class UAISenseConfig_Sight* SightConfig;
private:
	void OnRepeatTimer();
	FTimerHandle OnRepeatTimerHandle;
	float RepeatInterval;

	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;

	
	

	UFUNCTION()
	void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);

	
	
};

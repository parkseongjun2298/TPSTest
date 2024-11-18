// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include"NavigationSystem.h"
#include"Blueprint/AIBlueprintHelperLibrary.h"
#include"BehaviorTree/BehaviorTree.h"
#include"BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
AABAIController::AABAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_ABMonster.BB_ABMonster'"));

	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_ABMonster.BT_ABMonster'"));

	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	UE_LOG(LogTemp, Log, TEXT("ABAIController  called!"));
}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	UBlackboardComponent* BlackboardComp = Blackboard;



	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning,TEXT("Aicontroller no run."));
		}
		UE_LOG(LogTemp, Warning, TEXT("Aicontroller run"));
	}



}

void AABAIController::OnUnPossess()
{
	Super::OnUnPossess();
	

}

void AABAIController::OnRepeatTimer()
{
	auto CurPawn = GetPawn();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem)
		return;
	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);


		
	}
}

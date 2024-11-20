// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include"NavigationSystem.h"
#include"Blueprint/AIBlueprintHelperLibrary.h"
#include"BehaviorTree/BehaviorTree.h"
#include"BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include  "Perception/AISenseConfig_Sight.h"

const FName AABAIController::HomePosKey(TEXT("HOMEPOS"));
const FName AABAIController::PatrolPosKey(TEXT("PATROLPOS"));
const FName AABAIController::TargetKey(TEXT("Target"));

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

	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*PerceptionComponent);
	
	// �þ� ���� ����
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SightConfig->SightRadius = 800.f;           // �þ� �Ÿ�
		SightConfig->LoseSightRadius = 1200.f;       // ���� ���� �Ÿ�
		SightConfig->PeripheralVisionAngleDegrees = 90.0f; // �þ߰�
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

		PerceptionComponent->ConfigureSense(*SightConfig);
		PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	}
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AABAIController::OnTargetPerceived);

}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	UBlackboardComponent* BlackboardComp = Blackboard;



	if (UseBlackboard(BBAsset, BlackboardComp))
	{

		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning,TEXT("Aicontroller no run."));
		}

		
		
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

void AABAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{

	if (UBlackboardComponent* BlackboardComp = GetBlackboardComponent())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			BlackboardComp->SetValueAsObject(TargetKey, Actor);
		}
		else
		{
			BlackboardComp->ClearValue(TargetKey);
		}
	}
}

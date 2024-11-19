// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Perception/AIPerceptionComponent.h"
#include  "Perception/AISenseConfig_Sight.h"
UBTService_CheckPlayer::UBTService_CheckPlayer()
{
	NodeName = TEXT("CHECKPLAYER");

}

void UBTService_CheckPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

    UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
    if (!BlackboardComp) return;

    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn) return;


    // Perception으로부터 타겟 가져오기
    TArray<AActor*> PerceivedActors;
    UAIPerceptionComponent* Perception = AIController->FindComponentByClass<UAIPerceptionComponent>();
    if (Perception)
    {
        Perception->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
        if (PerceivedActors.Num() > 0)
        {
            BlackboardComp->SetValueAsObject(PlayerKey, PerceivedActors[0]);
        }
        else
        {
            BlackboardComp->ClearValue(PlayerKey);
        }
    }
}

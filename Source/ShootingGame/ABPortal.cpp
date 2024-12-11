// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPortal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AABPortal::AABPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;
    BoxComponent->SetBoxExtent(FVector(100.f, 100.f, 100.f));
    BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
    Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
  
    PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
    PortalMesh->SetupAttachment(RootComponent);
    Effect->SetupAttachment(RootComponent);
   
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AABPortal::OnOverlapBegin);

    TargetLevelName = FName(TEXT("Map2"));


    static ConstructorHelpers::FObjectFinder<UParticleSystem> P_HitBULLET(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMurdock/FX/Particles/Abilities/Passive/FX/P_Murdock_HotPursuit_Target.P_Murdock_HotPursuit_Target'"));
    if (P_HitBULLET.Succeeded())
    {
        Effect->SetTemplate(P_HitBULLET.Object);
        Effect->bAutoActivate = false;

    }



}

// Called when the game starts or when spawned
void AABPortal::BeginPlay()
{
	Super::BeginPlay();

    Effect->Activate(true);
}

// Called every frame
void AABPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        // 플레이어가 포탈에 들어갔는지 확인
        if (OtherActor->ActorHasTag("Player"))
        {
            // 맵 변경
            if (!TargetLevelName.IsNone())
            {
                UGameplayStatics::OpenLevel(this, TargetLevelName);
            }
        }
    }
}

void AABPortal::OnEffectFinished(UParticleSystemComponent* PSystem)
{
}


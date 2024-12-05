// Fill out your copyright notice in the Description page of Project Settings.


#include "ABBullet.h"
#include"Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"ABMonster.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h"
#include"ABCharacter.h"
// Sets default values
AABBullet::AABBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BULLET"));
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	
	CollisionComp->SetSphereRadius(13);
	RootComponent = CollisionComp;

	CollisionComp->SetCollisionProfileName(TEXT("ABBullet"));
	Bullet->SetCollisionProfileName(TEXT("NoCollision"));

	Bullet->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);
	Bullet->SetRelativeScale3D(FVector(0.25f));
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BULLET(TEXT("/Script/Engine.StaticMesh'/Game/ParagonMurdock/FX/Meshes/Heroes/Murdock/SM_ShottyMuzzleCone.SM_ShottyMuzzleCone'"));
	if (SM_BULLET.Succeeded())
	{
		Bullet->SetStaticMesh(SM_BULLET.Object);

	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_HitBULLET(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMurdock/FX/Particles/Abilities/Primary/FX/P_PlasmaShot_Hit_Player.P_PlasmaShot_Hit_Player'"));
	if (P_HitBULLET.Succeeded())
	{
		Effect->SetTemplate(P_HitBULLET.Object);
		Effect->bAutoActivate = false;

	}

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->SetUpdatedComponent(CollisionComp);
	MovementComp->InitialSpeed = 7000.f;
	MovementComp->MaxSpeed = 7000;
	MovementComp->bShouldBounce = false;
	MovementComp->bRotationFollowsVelocity = true;
	

	InitialLifeSpan = 1.0f;

	

	
}

// Called when the game starts or when spawned
void AABBullet::BeginPlay()
{
	Super::BeginPlay();
	

	
}

void AABBullet::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (CollisionComp)
	{
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AABBullet::OnCharacterOverlap);

	}
}

// Called every frame
void AABBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	


}

void AABBullet::FireInDirection(const FVector& ShootDirection)
{
	MovementComp->Velocity = ShootDirection * MovementComp->InitialSpeed;
}

void AABBullet::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AABMonster* HitMonster = Cast<AABMonster>(OtherActor);

	AABCharacter* HitPlayer = Cast<AABCharacter>(OtherActor);
	if (HitMonster|| HitPlayer)
	{
		FDamageEvent DamageEvent;

		Effect->Activate(true);
		//UE_LOG(LogTemp, Warning, TEXT("HIt"));
		if(HitMonster)
			HitMonster->TakeDamage(10.f, DamageEvent, GetInstigatorController(),this);
		if (HitPlayer)
			HitPlayer->TakeDamage(10.f, DamageEvent, GetInstigatorController(), this);
		
		Effect->OnSystemFinished.AddDynamic(this, &AABBullet::OnEffectFinished);
		
		
		//Destroy();
	}

	else
	{
		Effect->Activate(true);
		Effect->OnSystemFinished.AddDynamic(this, &AABBullet::OnEffectFinished);
	}








}

void AABBullet::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}


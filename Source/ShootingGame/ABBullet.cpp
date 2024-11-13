// Fill out your copyright notice in the Description page of Project Settings.


#include "ABBullet.h"
#include"Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"ABMonster.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h"

// Sets default values
AABBullet::AABBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BULLET"));
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));

	
	CollisionComp->SetSphereRadius(13);
	RootComponent = CollisionComp;

	CollisionComp->SetCollisionProfileName(TEXT("ABBullet"));
	Bullet->SetCollisionProfileName(TEXT("NoCollision"));

	Bullet->SetupAttachment(RootComponent);

	Bullet->SetRelativeScale3D(FVector(0.25f));
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BULLET(TEXT("/Script/Engine.StaticMesh'/Game/ParagonMurdock/FX/Meshes/Heroes/Murdock/SM_ShottyMuzzleCone.SM_ShottyMuzzleCone'"));
	if (SM_BULLET.Succeeded())
	{
		Bullet->SetStaticMesh(SM_BULLET.Object);

	}


	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->SetUpdatedComponent(CollisionComp);
	MovementComp->InitialSpeed = 7000.f;
	MovementComp->MaxSpeed = 7000;
	MovementComp->bShouldBounce = false;
	MovementComp->bRotationFollowsVelocity = true;
	

	InitialLifeSpan = 3.0f;
	
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
	if (HitMonster)
	{
		FDamageEvent DamageEvent;
		UE_LOG(LogTemp, Warning, TEXT("HIt"));
		HitMonster->TakeDamage(10.f, DamageEvent, GetInstigatorController(),this);
		Destroy();
	}
}


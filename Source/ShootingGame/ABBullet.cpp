// Fill out your copyright notice in the Description page of Project Settings.


#include "ABBullet.h"
#include"Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

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

	Bullet->SetupAttachment(RootComponent);
	Bullet->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Bullet->SetRelativeScale3D(FVector(0.25f));
	//Bullet->SetRelativeLocation(FVector(0, 0, -12.5f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BULLET(TEXT("/Script/Engine.StaticMesh'/Game/ParagonMurdock/FX/Meshes/Heroes/Murdock/SM_ShottyMuzzleCone.SM_ShottyMuzzleCone'"));
	if (SM_BULLET.Succeeded())
	{
		Bullet->SetStaticMesh(SM_BULLET.Object);

	}


	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->SetUpdatedComponent(CollisionComp);
	MovementComp->InitialSpeed = 5000.f;
	MovementComp->MaxSpeed = 5000;
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
	//CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AABBullet::OnCharacterOverlap);
	//여기 이상한듯
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

	UE_LOG(LogTemp, Warning, TEXT("OVerlap"));
}


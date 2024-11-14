// Fill out your copyright notice in the Description page of Project Settings.


#include "ABMonster.h"
#include"ABMonsterStatComponent.h"
#include"ABMonsterAnimInstance.h"
#include"Components/CapsuleComponent.h"
#include"ABBullet.h"
#include"ABGameInstance.h"
// Sets default values
AABMonster::AABMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator
	(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerAS_Name(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMurdock/Characters/Heroes/Murdock/Meshes/Murdock.Murdock'"));
	if (PlayerAS_Name.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerAS_Name.Object);

	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UABMonsterAnimInstance> Player_Animation(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/ANI_ABMonster.ANI_ABMonster_C'"));
	if (Player_Animation.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Player_Animation.Class);

	}

	bAttackMode = false;


	
	
	
	GetCapsuleComponent()->SetupAttachment(RootComponent);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABMonster"));


	BulletList = AABBullet::StaticClass();


	CharacterStat = CreateAbstractDefaultSubobject<UABMonsterStatComponent>(TEXT("CHARACTERSTAT"));



}

// Called when the game starts or when spawned
void AABMonster::BeginPlay()
{
	Super::BeginPlay();

	CharacterStat->SetNewLevel(1);

}

// Called every frame
void AABMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Mon HP:%f"), CharacterStat->Get_HP());
	if (CharacterStat->Get_HP() <= 0)
	{
	
			SetDead();
			

	}
	
}

// Called to bind functionality to input


void AABMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABAnim = Cast<UABMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	
	
	
}

float AABMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage=Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CharacterStat->Set_HP(-FinalDamage);
	return FinalDamage;
}

void AABMonster::SetDead()
{
	bDead = true;
	ABAnim = Cast<UABMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	ABAnim->OnDeadDelegate.AddLambda([this]()->void {

		Destroy();
		});


		
}



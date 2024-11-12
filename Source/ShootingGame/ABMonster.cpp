// Fill out your copyright notice in the Description page of Project Settings.


#include "ABMonster.h"
#include"ABMonsterStatComponent.h"
#include"ABMonsterAnimInstance.h"
#include"Components/CapsuleComponent.h"
// Sets default values
AABMonster::AABMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerAS_Name(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMurdock/Characters/Heroes/Murdock/Meshes/Murdock.Murdock'"));
	if (PlayerAS_Name.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerAS_Name.Object);

	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> Player_Animation(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/ANI_ABChar.ANI_ABChar_C'"));
	if (Player_Animation.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Player_Animation.Class);

	}

	bAttackMode = false;


	//CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MonsterCapsuleCollision"));
	//CapsuleCollision->InitCapsuleSize(42.f, 96.0f); // ũ�� ����
	//CapsuleCollision->SetupAttachment(RootComponent); // RootComponent�� ����
	
	
	GetCapsuleComponent()->SetupAttachment(RootComponent);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABMonster"));

}

// Called when the game starts or when spawned
void AABMonster::BeginPlay()
{
	Super::BeginPlay();
	


}

// Called every frame
void AABMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AABMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AABMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABAnim = Cast<UABMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	//�Ѿ˹߻�
	//ABAnim->OnFireBulletDelegate.AddLambda([this]()->void {

	//	if (ABPlayerState->GetCurBullet() > 0)
	//	{

	//		FTransform fireposition = GetMesh()->GetSocketTransform(TEXT("Muzzle"));


	//		AABBullet* Bullet = GetWorld()->SpawnActor<AABBullet>(BulletList, fireposition);
	//		if (Bullet)
	//		{
	//			FVector LaunchDirection = Camera->GetForwardVector();

	//			//FVector LaunchDirection = Camera->GetRightVector(); �̰� ��ź�������°ɷ��ϴ� ���־���

	//			Bullet->FireInDirection(LaunchDirection);
	//		}
	//		ABPlayerState->SetCurBullet(-1);

	//	}




	//	});

	////������
	//ABAnim->OnReloadDelegate.AddLambda([this]()->void {


	//	bReload = false;
	//	ABPlayerState->ReLoadBullet(ABPlayerState->GetMaxBullet());
	//	});

}


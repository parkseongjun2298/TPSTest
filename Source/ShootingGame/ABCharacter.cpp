// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include"ABBullet.h"
#include "Camera/CameraComponent.h"
#include"ABAnimInstance.h"
// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f),FRotator
	(0.f,-90.f,0.f));
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 110.f));
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerAS_Name (TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMurdock/Characters/Heroes/Murdock/Meshes/Murdock.Murdock'"));
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

	GetCharacterMovement()->JumpZVelocity = 600.f;

	BulletList = AABBullet::StaticClass();

	

}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("RightLeft"), this, &AABCharacter::RightLeft);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);
	

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AABCharacter::NormalAttackStart);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Released, this, &AABCharacter::NormalAttackEnd);
	PlayerInputComponent->BindAction(TEXT("Zoom"), EInputEvent::IE_Pressed, this, &AABCharacter::Zoom);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AABCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Reroad"), EInputEvent::IE_Pressed,this, &AABCharacter::Reload);
}

void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABAnim = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());

	ABAnim->OnFireBulletDelegate.AddLambda([this]()->void {

		


		FTransform fireposition = GetMesh()->GetSocketTransform(TEXT("Muzzle"));


		AABBullet* Bullet = GetWorld()->SpawnActor<AABBullet>(BulletList, fireposition);
		if (Bullet)
		{
			FVector LaunchDirection = Camera->GetForwardVector();

			//FVector LaunchDirection = Camera->GetRightVector(); ÀÌ°É ÃÑÅº¶³¾îÁö´Â°É·ÎÇÏ´Ï ¸ÚÀÖ¾îÁü

			Bullet->FireInDirection(LaunchDirection);
		}

		});

	ABAnim->OnReloadDelegate.AddLambda([this]()->void {

		bReload = false;
		});

}

void AABCharacter::UpDown(float Axis)
{
	if (!bAttackMode)
	{
		AddMovementInput(GetActorForwardVector(), Axis);
	}
}

void AABCharacter::RightLeft(float Axis)
{
	if (!bAttackMode)
	{
		AddMovementInput(GetActorRightVector(), Axis);

	}
}

void AABCharacter::LookUp(float Axis)
{
	AddControllerPitchInput(-Axis);
}

void AABCharacter::Turn(float Axis)
{
	AddControllerYawInput(Axis);
}

void AABCharacter::NormalAttackEnd()
{
	bAttackMode = false;
}

void AABCharacter::Zoom()
{
	++iZoomCount;
	if (iZoomCount % 2 == 1)
	{
		
		SpringArm->TargetArmLength = -400.f;

	}
	else
	{
		
		SpringArm->TargetArmLength = 600.f;
	}
}

void AABCharacter::Reload()
{
	bReload = true;
}

void AABCharacter::NormalAttackStart()
{
	bAttackMode = true;
	
	


}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"
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
	SpringArm->TargetArmLength = 400.f;
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

}

void AABCharacter::UpDown(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

void AABCharacter::RightLeft(float Axis)
{

	AddMovementInput(GetActorRightVector(), Axis);
}

void AABCharacter::LookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

void AABCharacter::Turn(float Axis)
{
	AddControllerYawInput(Axis);
}

void AABCharacter::NormalAttackEnd()
{
	bAttackMode = false;
}

void AABCharacter::NormalAttackStart()
{
	bAttackMode = true;

}


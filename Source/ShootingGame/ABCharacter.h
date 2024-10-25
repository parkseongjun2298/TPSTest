// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UCLASS()
class SHOOTINGGAME_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents()override;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	bool bAttackMode = false;
	int32 iZoomCount = 0;

	bool bReload = false;
	

	UPROPERTY(EditAnywhere, Category = "Bullet")
	TSubclassOf<class AABBullet> BulletList;
	//SpawnActor 로 소환시 uclass를 쓰므로 TSubclassOf로 해야한다
	
	UPROPERTY()
	class UABAnimInstance* ABAnim;


	int MaxBulletNum = 0;
	int BulletNum = 0;


private:
		void UpDown(float Axis);
		void RightLeft(float Axis);
		void LookUp(float Axis);
		void Turn(float Axis);
		void NormalAttackStart();
		void NormalAttackEnd();
		void Zoom();
		void Reload();




};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "ABBullet.generated.h"

UCLASS()
class SHOOTINGGAME_API AABBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	UStaticMeshComponent* Bullet;

	UPROPERTY(VisibleAnywhere, Category = Bullet)
	class UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, Category = Bullet)
	class USphereComponent* CollisionComp;

	void FireInDirection(const FVector& ShootDirection);

private:
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

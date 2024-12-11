// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "GameFramework/Actor.h"
#include "ABPortal.generated.h"

UCLASS()
class SHOOTINGGAME_API AABPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


   
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal")
    class UBoxComponent* BoxComponent;

   
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal")
    class UStaticMeshComponent* PortalMesh;

  
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
    FName TargetLevelName;

   
    UPROPERTY(VisibleAnywhere, Category = "Effect")
    UParticleSystemComponent* Effect;

private:

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
        class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);


    UFUNCTION()
    void OnEffectFinished(class UParticleSystemComponent* PSystem);
};

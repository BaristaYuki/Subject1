// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Corn.generated.h"

UCLASS()
class PK_API ACorn : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACorn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BoxComp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UParticleSystemComponent* ParticleSystemComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		
	bool bIsHit;

	void CheckHit();

	void Move();
};

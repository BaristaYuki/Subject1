// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Controller.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DribblerManager.generated.h"

UCLASS()
class PK_API ADribblerManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADribblerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere)
		class ADribbler* Dribbler;

	UPROPERTY(EditDefaultsOnly, Category = Dribbler)
		TSubclassOf<class ADribbler>SubDribbler;

	TArray<AActor*>ArrDribbler;

	UPROPERTY()
	AController* OurController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	uint8_t FindBallPossecer();

	int32 DecideDestination();

	UFUNCTION(BlueprintCallable)
	void hoge();

};

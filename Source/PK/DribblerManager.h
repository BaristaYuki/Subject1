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

	//Dribblerを入れる配列
	UPROPERTY()
	TArray<AActor*>ArrDribbler;

	UPROPERTY()
	AController* OurController;

	//ボール保持者と他の人との２点間のベクトルを保持する配列
	UPROPERTY()
	TArray<FVector>VecArray;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	uint8_t FindBallPossecer();

	int32 DecideDestination(uint8_t i);

	void MakeVector(TArray<FVector>VecArray, uint8_t index);

	//デリゲートの受信側関数
	UFUNCTION(BlueprintCallable)
	void hoge();

};

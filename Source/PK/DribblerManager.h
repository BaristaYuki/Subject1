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
	UPROPERTY(EditAnywhere)
	class ADribbler* Dribbler2;

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

	//ボール所有者探す
	uint8_t FindBallPossecer();
	//カメラの向きから誰にパスを出すか決める
	void DecideDestination(uint8_t i);

	float CulcTheta(FVector Base, FVector V);

	void FindMinDegree(uint8_t index, FVector PasserVec);

	FVector SetPassVector(uint8_t index);

	uint8_t ReceiverIndex;

	//デリゲートの受信側関数
	UFUNCTION(BlueprintCallable)
	void hoge();

};

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

	UPROPERTY(EditDefaultsOnly, Category = Ball)
	TSubclassOf<class ABall>BallClass;

	UPROPERTY()
	ABall* Ball;

	//Dribblerを入れる配列
	UPROPERTY()
	TArray<AActor*>ArrDribbler;

	UPROPERTY()
	AController* OurController;

	//ボール保持者と他の人との２点間のベクトルを保持する配列
	UPROPERTY()
	TArray<FVector>VecArray;

	uint8_t ReceiverIndex;

	uint8_t MyIndex;

	UFUNCTION()
	void SpawnBall();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//ボール所有者探す
	uint8_t FindBallPossecer();
	//カメラの向きから誰にパスを出すか決める
	void DecideDestination();

	float CulcTheta(const FVector Base, const FVector V);

	void FindMinDegree(const FVector PasserVec);

	FVector SetPassVector();

	void Pass(const FVector Vec);

	UFUNCTION(BlueprintCallable)
	void Dribble();

	//デリゲートの受信側関数
	UFUNCTION(BlueprintCallable)
	void hoge();

};

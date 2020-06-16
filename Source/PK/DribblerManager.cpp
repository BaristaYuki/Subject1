// Fill out your copyright notice in the Description page of Project Settings.

//プレイヤーのパスの相手を管理する

#include "DribblerManager.h"
#include "Dribbler.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADribblerManager::ADribblerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADribblerManager::BeginPlay()
{
	Super::BeginPlay();

	SubDribbler = ADribbler::StaticClass();
	//ドリブラーを配列に格納
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SubDribbler, ArrDribbler);

	/*
	for (TActorIterator<ADribbler>DribblerItr(GetWorld()); DribblerItr; ++DribblerItr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ArrDribbler.Num()), true, FVector2D(3.0f, 3.0f));
		ADribbler* Dribbler = *DribblerItr;
		Dribbler->PassDispather.AddDynamic(this, &ADribblerManager::hoge );
		//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		AController* OurController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurController)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("kita")), true, FVector2D(3.0f, 3.0f));
		}
	
	}*/

	for (uint8_t i = 0; i < ArrDribbler.Num(); i++)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ArrDribbler.Num()), true, FVector2D(3.0f, 3.0f));
		ADribbler* Dribbler = Cast<ADribbler>(ArrDribbler[i]);
		//デリゲートに追加
		Dribbler->PassDispather.AddDynamic(this, &ADribblerManager::hoge);
	}

	//コントローラの取得
	OurController = UGameplayStatics::GetPlayerController(this, 0);
	OurController->Possess(Cast<APawn>(ArrDribbler[0]));
	
}

// Called every frame
void ADribblerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 誰がボールを持っているかを探す
uint8_t ADribblerManager::FindBallPossecer()
{
	for (uint8_t index = 0; index < ArrDribbler.Num(); index++)
	{
		Dribbler = Cast<ADribbler>(ArrDribbler[index]);
		if (Dribbler->GetbIsPossece())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("found")), true, FVector2D(3.0f, 3.0f));
			return index;
		}
	}
	return -1;
}

//カメラの向きから誰にパスを出すか決める
int32 ADribblerManager::DecideDestination(uint8_t i)
{
	Dribbler = Cast<ADribbler>(ArrDribbler[i]);

	Dribbler->SetDirection();
	Dribbler->Direction.Normalize();

	return int32();
}

// 人と人の角度を求めて配列に保持
void ADribblerManager::MakeVector(TArray<FVector> VecArray, uint8_t index)
{
	Dribbler = Cast<ADribbler>(ArrDribbler[index]);

	//ボール保持者の座標
	FVector BaseVector = Dribbler->GetActorLocation();
	
	for (uint8_t i = 0; i < ArrDribbler.Num(); i++)
	{
		if (i == index) { continue; }
		else
		{
			VecArray[i] = ArrDribbler[i]->GetActorLocation() - BaseVector;
		}
	}

}

//デリゲートで呼び出す関数
void ADribblerManager::hoge()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("hoge")), true, FVector2D(3.0f, 3.0f));
	uint8_t m_index = FindBallPossecer();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(m_index), true, FVector2D(3.0f, 3.0f));
	DecideDestination(m_index);
}

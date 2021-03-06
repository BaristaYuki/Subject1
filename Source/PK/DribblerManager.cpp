// Fill out your copyright notice in the Description page of Project Settings.

//プレイヤーのパスの相手を管理する

#include "DribblerManager.h"
#include "Dribbler.h"
#include "Ball.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ADribblerManager::ADribblerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyIndex = 0;
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
	SpawnBall();
	for (uint8_t i = 0; i < ArrDribbler.Num(); i++)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ArrDribbler.Num()), true, FVector2D(3.0f, 3.0f));
		ADribbler* Dribbler = Cast<ADribbler>(ArrDribbler[i]);
		if (i == 0) { Dribbler->SetIsPossece(true); }
		//デリゲートに追加
		Dribbler->PassDispather.AddDynamic(this, &ADribblerManager::hoge);
		Dribbler->HitDispather.AddDynamic(this, &ADribblerManager::Dribble);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ArrDribbler.Num()), true, FVector2D(1.0f, 1.0f));

	//コントローラの取得
	OurController = UGameplayStatics::GetPlayerController(this, 0);
	OurController->Possess(Cast<APawn>(ArrDribbler[0]));
}

void ADribblerManager::SpawnBall()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters Params;
		//Params.Owner = this;
	//	Ball = World->SpawnActor<ABall>(BallClass, ArrDribbler[MyIndex]->GetActorLocation() + FVector(100.0f, 0.0f, 30.0f), FRotator(), Params);
		Ball = World->SpawnActor<ABall>(BallClass, FVector(-1000.0f, -800.0f, 30.0f), FRotator(), Params);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, ArrDribbler[MyIndex]->GetActorLocation().ToString(), true, FVector2D(3.0f, 3.0f));

	}
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
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("BallPosesserfound")), true, FVector2D(3.0f, 3.0f));
			return index;
		}
	}
	return -1;
}

//カメラの向きから誰にパスを出すか決める
void ADribblerManager::DecideDestination()
{
	Dribbler = Cast<ADribbler>(ArrDribbler[MyIndex]);

	//向きからベクトルセット->Dribbler.Direction
	Dribbler->SetDirection();
	//一応正規化
	Dribbler->Direction.Normalize();

	//パス出す相手を決める
	FindMinDegree(Dribbler->Direction);
}

// 人と人の角度を求めて配列に保持 配列いらない
void ADribblerManager::FindMinDegree(FVector PasserVec)
{
	float MinDegree = 400;
	Dribbler = Cast<ADribbler>(ArrDribbler[MyIndex]);

	//ボール保持者の座標
	FVector BaseVector = Dribbler->GetActorLocation();
	
	for (uint8_t i = 0; i < ArrDribbler.Num(); i++)
	{
		if (i == MyIndex) { continue; }
		else
		{
			//VecArray[i] = ArrDribbler[i]->GetActorLocation() - BaseVector;
			if (MinDegree > CulcTheta(PasserVec, ArrDribbler[i]->GetActorLocation() - BaseVector))
			{
				ReceiverIndex = i;
			}
		}
	}
}

float ADribblerManager::CulcTheta(FVector Base, FVector V)
{
	float Degree;
	FVector Vec;
	float CosTheta;

	//Base.Size() * V.Size()* CosTheta = Vec;
	CosTheta = Vec.DotProduct(Base, V) / (Base.Size() * V.Size());

	//角度求める
	Degree = FMath::Abs(FMath::Acos(CosTheta));

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::SanitizeFloat(Degree), true, FVector2D(3.0f, 3.0f));

	return Degree;
}

FVector ADribblerManager::SetPassVector()
{
	FVector MyVec = ArrDribbler[ReceiverIndex]->GetActorLocation() - ArrDribbler[MyIndex]->GetActorLocation();

	return MyVec;
}

//パスをする
void ADribblerManager::Pass(const FVector Vec)
{
	Dribbler = Cast<ADribbler>(ArrDribbler[MyIndex]);
	Ball->Pass(SetPassVector());
}

//DribblerがOverlapイベントを起こしたらデリゲートで受信。　そしてドリブル
void ADribblerManager::Dribble()
{
	Dribbler = Cast<ADribbler>(ArrDribbler[MyIndex]);
	Dribbler->SetDirection();
	Ball->Dribble(Dribbler->Direction);
}

//デリゲートから呼ばれてパスするために色んなことする
void ADribblerManager::hoge()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("hoge")), true, FVector2D(3.0f, 3.0f));
	//まずボール持っている人探す
	MyIndex = FindBallPossecer();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("m-index :"))+FString::FromInt(MyIndex), true, FVector2D(3.0f, 3.0f));
	
	if (MyIndex < 0 && MyIndex >= ArrDribbler.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("m-indexfalse: ")), true, FVector2D(3.0f, 3.0f));
		
	}
	else {
		DecideDestination();

		//パスをする
		Dribbler = Cast<ADribbler>(ArrDribbler[MyIndex]);
		//Dribbler->Pass(SetPassVector(m_index));

		Dribbler->SetIsPossece(false);

		//pass受ける側のクラス Posseceフラグをtrueに
		Dribbler2 = Cast<ADribbler>(ArrDribbler[ReceiverIndex]);
		Dribbler2->SetIsPossece(true);
		//コントローラの所有者の変更
		OurController->Possess(Cast<APawn>(ArrDribbler[ReceiverIndex]));
	}
}

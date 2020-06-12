// Fill out your copyright notice in the Description page of Project Settings.

//プレイヤーのパスの相手を管理する

#include "DribblerManager.h"
#include "Dribbler.h"
#include "Engine/Engine.h"
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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SubDribbler, ArrDribbler);

	
}

// Called every frame
void ADribblerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 誰がボールを持っているかを探す
int32 ADribblerManager::FindBallPossecer()
{
	for (int32 index = 0; index < ArrDribbler.Num(); index++)
	{
		Dribbler = Cast<ADribbler>(ArrDribbler[index]);
		if (Dribbler->GetbIsPossece())
		{
			return index;
		}
	}
	return -1;
}

int32 ADribblerManager::DecideDestination()
{
	return int32();
}


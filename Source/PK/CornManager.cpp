// Fill out your copyright notice in the Description page of Project Settings.


#include "CornManager.h"
#include "Corn.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACornManager::ACornManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACornManager::BeginPlay()
{
	Super::BeginPlay();

	SubCorn = ACorn::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SubCorn, ArrCorn);

	Corn = Cast<ACorn>(ArrCorn[0]);

	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ArrCorn.Num()), true, FVector2D(1.0f, 1.0f));
	
	/*
	World = GetWorld();

	for (TActorIterator<ACorn>CornItr(World); CornItr; ++CornItr)
	{
		Corn = *CornItr;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("ITR")), true, FVector2D(1.0f, 1.0f));
	}
	*/
}

// Called every frame
void ACornManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCorn();
}

void ACornManager::MoveCorn()
{
	Corn->Move();
}
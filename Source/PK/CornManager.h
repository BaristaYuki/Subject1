// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "CornManager.generated.h"

UCLASS()
class PK_API ACornManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACornManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY()
	UWorld* World;

	UPROPERTY()
	FVector Loc;

	UPROPERTY(EditAnyWhere)
		class ACorn* Corn;
	
	UPROPERTY(EditDefaultsOnly, Category = Corn)
		TSubclassOf<class ACorn>SubCorn;

	TArray<AActor*>ArrCorn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveCorn();
	
};

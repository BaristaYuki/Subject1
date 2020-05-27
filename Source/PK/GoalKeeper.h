// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimerManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GoalKeeper.generated.h"

UCLASS()
class PK_API AGoalKeeper : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGoalKeeper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BluePrintCallable)
	void DecideDirection();
	UFUNCTION(BluePrintCallable)
	void Init();
	UFUNCTION()
	void MoveRight(float value);
	UFUNCTION()
	void MoveLeft(float value);

	void CheckTimer();
	void MoveKeeper();
	
	FTimerHandle CountdownTimerHandle;

	UPROPERTY(EditAnywhere)
	int32 CountdownTime;

	UPROPERTY(EditAnyWhere)
	FVector Loc;

private:
	int32 seed;
	int32 Y_Move;
	int32 Z_Move;

};

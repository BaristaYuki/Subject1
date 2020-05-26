// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	void DecideDirection();

	UFUNCTION(BluePrintCallable)
	void Init();
	UFUNCTION(BluePrintCallable)
	void MoveRightUp();
	UFUNCTION(BluePrintCallable)
	void MoveRightDown();
	UFUNCTION(BluePrintCallable)
	void MoveLeftUp();
	UFUNCTION(BluePrintCallable)
	void MoveLeftDown();

	UPROPERTY(EditAnywhere)
	bool Kicked;

private:
	int32 seed;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "BallPawn.generated.h"

UCLASS()
class PK_API ABallPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	void MoveForward();

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ShootTargetMesh;

	//ボールを蹴る関数
	UFUNCTION(BluePrintCallable)
	void Shoot();
	UFUNCTION(BluePrintCallable)
	void SetPosition();
	UFUNCTION(BluePrintCallable)
	void ShootRandom();

	void SpawnBall();
	void MoveTargetY(float AxisValue);
	void MoveTargetZ(float AxisValue);

	UFUNCTION(BluePrintCallable)
	void AddScore();
	FVector Temp;
	bool Kicked;

	//ボールを蹴る座標
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector ShootingPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector TargetDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FRotator TargetRotation;


	UPROPERTY(EditDefaultsOnly, Category = Ball)
		TSubclassOf<class ABall>BallClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector RootLocation = FVector(450.0f, 0.0f, 100.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector CameraRelativeLocation = FVector(200.0f, 0.0f, 0.0f);

	//１つだけBallをインスタンス化する
	ABall* Ball;
	UPROPERTY(BluePrintReadWrite)
	int32 Score_1P = 0;
	UPROPERTY(BluePrintReadWrite)
	int32 Score_2P = 0;
	UPROPERTY(BluePrintReadWrite)
	bool CheckGoal;

};
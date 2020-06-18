// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalKeeper.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Math/RotationMatrix.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"

// Sets default values
AGoalKeeper::AGoalKeeper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Keeperの初期位置
	Loc = FVector(-450.0f, 0.0f, 79.0f);
	Direction = FVector(0.0f, -1.0f, 0.0f);
	
}

// Called when the game starts or when spawned
void AGoalKeeper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoalKeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGoalKeeper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoalKeeper::MoveRight);
	PlayerInputComponent->BindAxis("MoveLeft", this, &AGoalKeeper::MoveLeft);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGoalKeeper::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AGoalKeeper::StopJump);
}

void AGoalKeeper::DecideDirection()
{
	/*seed = FMath::RandRange(0, 3);
	if (seed == 0)
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AGoalKeeper::MoveRightUp, 0.05f, true);
	}
	else if (seed == 1)
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AGoalKeeper::MoveRightDown, 0.05f, true);
	}
	else if (seed == 2)
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AGoalKeeper::MoveLeftUp, 0.05f, true);
	}
	else if (seed == 3)
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AGoalKeeper::MoveLeftDown, 0.05f, true);
	}*/


	Z_Move = FMath::RandRange(0, 20);
	Y_Move = FMath::RandRange(-40, 40);
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AGoalKeeper::MoveKeeper, 0.05f, true);
}

//キーパーの場所とTimerをリセットする
void AGoalKeeper::Init()
{
	Loc = FVector(-480.0f, 0.0f, 79.0f);
	SetActorLocation(Loc);
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	CountdownTime = 12;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Init"), true, FVector2D(3.0f, 3.0f));
}


//Timerのチェック
void AGoalKeeper::CheckTimer()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(CountdownTime), true, FVector2D(3.0f, 3.0f));
	CountdownTime--;
	if (CountdownTime < 0)
	{
		Init();
	}
}

//適当に乱数を発生させて0.05秒ずつ座標を更新　キーパーを操作していないとき
void AGoalKeeper::MoveKeeper()
{
	Loc.Y += Y_Move;
	Loc.Z += Z_Move;
	SetActorLocation(Loc);
	CheckTimer();
}

//キーパー操作をしているときの移動
void AGoalKeeper::MoveRight(float value)
{
	AddMovementInput(Direction, value);
}

void AGoalKeeper::MoveLeft(float value)
{
	AddMovementInput(Direction, value);
}

void AGoalKeeper::StartJump()
{
	bPressedJump = true;
}

void AGoalKeeper::StopJump()
{
	bPressedJump = false;
}


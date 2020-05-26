// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalKeeper.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"


// Sets default values
AGoalKeeper::AGoalKeeper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Keeper‚Ì‰ŠúˆÊ’u
	Loc = FVector(-450.0f, 0.0f, 79.0f);
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


	Z_Move = FMath::RandRange(0, 30);
	Y_Move = FMath::RandRange(-30, 30);
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AGoalKeeper::MoveKeeper, 0.05f, true);
}


void AGoalKeeper::Init()
{
	Loc = FVector(-480.0f, 0.0f, 79.0f);
	SetActorLocation(Loc);
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	CountdownTime = 10;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Init"), true, FVector2D(3.0f, 3.0f));
}


void AGoalKeeper::MoveRightUp()
{
	Loc.Y += 20.0f;
	Loc.Z += 5.0f;
	SetActorLocation(Loc);
	CheckTimer();
}

void AGoalKeeper::MoveRightDown()
{
	Loc.Y += 20.0f;
	SetActorLocation(Loc);
	CheckTimer();
}

void AGoalKeeper::MoveLeftUp()
{
	Loc.Y -= 20.0f;
	Loc.Z += 5.0f;
	SetActorLocation(Loc);
	CheckTimer();
}

void AGoalKeeper::MoveLeftDown()
{
	Loc.Y -= 20.0f;
	SetActorLocation(Loc);
	CheckTimer();
}

void AGoalKeeper::CheckTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(CountdownTime), true, FVector2D(3.0f, 3.0f));
	CountdownTime--;
	if (CountdownTime < 0)
	{
		Init();
	}
}

void AGoalKeeper::MoveKeeper()
{
	Loc.Y += Y_Move;
	Loc.Z += Z_Move;
	SetActorLocation(Loc);
	CheckTimer();
}

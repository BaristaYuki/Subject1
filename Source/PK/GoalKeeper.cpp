// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalKeeper.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"


// Sets default values
AGoalKeeper::AGoalKeeper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Kicked = false;
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
	seed = FMath::RandRange(0, 3);
	if (seed == 0)
	{
		MoveRightUp();
	}
	else if (seed == 1)
	{
		MoveRightDown();
	}
	else if (seed == 2)
	{
		MoveLeftUp();
	}
	else if (seed == 3)
	{
		MoveLeftDown();
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::FromInt(seed), true, FVector2D(3.0f, 3.0f));
}


void AGoalKeeper::Init()
{
}

void AGoalKeeper::MoveRightUp()
{
}

void AGoalKeeper::MoveRightDown()
{
}

void AGoalKeeper::MoveLeftUp()
{
}

void AGoalKeeper::MoveLeftDown()
{
}


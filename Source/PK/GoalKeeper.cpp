// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalKeeper.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"


// Sets default values
AGoalKeeper::AGoalKeeper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Keeper�̏����ʒu
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


	Z_Move = FMath::RandRange(0, 30);
	Y_Move = FMath::RandRange(-30, 30);
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AGoalKeeper::MoveKeeper, 0.05f, true);
}

//�L�[�p�[�̏ꏊ��Timer�����Z�b�g����
void AGoalKeeper::Init()
{
	Loc = FVector(-480.0f, 0.0f, 79.0f);
	SetActorLocation(Loc);
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	CountdownTime = 10;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Init"), true, FVector2D(3.0f, 3.0f));
}


//Timer�̃`�F�b�N
void AGoalKeeper::CheckTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(CountdownTime), true, FVector2D(3.0f, 3.0f));
	CountdownTime--;
	if (CountdownTime < 0)
	{
		Init();
	}
}

//�K���ɗ����𔭐�������0.05�b�����W���X�V
void AGoalKeeper::MoveKeeper()
{
	Loc.Y += Y_Move;
	Loc.Z += Z_Move;
	SetActorLocation(Loc);
	CheckTimer();
}

void AGoalKeeper::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);

}

void AGoalKeeper::MoveLeft(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
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

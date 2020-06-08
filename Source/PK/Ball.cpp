// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	
	RootComponent = CollisionComponent;
	//オブジェクトだけ作成　アタッチはShootInDirection()で行う
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	//試しているだけ
	InitialLifeSpan = 0;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->SetGenerateOverlapEvents(true);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::ShootInDirection(FVector ShootDirection)
{
	//BallPawn::shootが呼び出されたらConponentをアタッチしVelocityを設定しBallを動かす
	//無理やりBallPawnとの座標の差を埋める
	ShootDirection = ShootDirection - FVector(200.0f, 0.0f, 0.0f);

	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 1.8f;
	ProjectileMovementComponent->MaxSpeed = 10000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.6f;
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;

}

//DribbleしているときDribblerがボールとHit判定がでたらボールを動かす
void ABall::Dribble(FVector Direction)
{
	
	Direction *= 10.0f;
	Direction += FVector(0.0f, 0.0f, 5.f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Direction.ToString(), true, FVector2D(1.0f, 1.0f));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 50.f;
	ProjectileMovementComponent->MaxSpeed = 10000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.6f;
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;

}
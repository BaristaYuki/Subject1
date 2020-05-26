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
	//�I�u�W�F�N�g�����쐬�@�A�^�b�`��ShootInDirection()�ōs��
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	//�����Ă��邾��
	InitialLifeSpan = 0;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABall::ShootInDirection(FVector ShootDirection)
{
	//BallPawn::shoot���Ăяo���ꂽ��Conponent���A�^�b�`��Velocity��ݒ肵Ball�𓮂���
	//�������BallPawn�Ƃ̍��W�̍��𖄂߂�
	ShootDirection = ShootDirection - FVector(200.0f, 0.0f, 0.0f);

	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 2.0f;
	ProjectileMovementComponent->MaxSpeed = 10000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.6f;
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;

}

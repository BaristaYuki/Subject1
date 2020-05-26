// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPawn.h"
#include "Ball.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABallPawn::ABallPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Camera���Z�b�g
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("UScene"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//FVector RootLocation = RootComponent->GetComponentLocation();  �����̓G�f�B�^���N���b�V��������BRootComponent�ɂ͎��̂��Ȃ�!?

	//�V���[�g�^�[�Q�b�g�p�̃��b�V���̃A�^�b�`
	ShootTargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShootTarget"));
	ShootTargetMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded()) {
		ShootTargetMesh->SetStaticMesh(SphereVisualAsset.Object);
		//�S�[�����ʏ�œ���������
		ShootTargetMesh->SetRelativeLocation(RootLocation-TargetDirection + FVector(0.0f, 0.0f, 100.0f));
	}

	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	Kicked = false;
}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("Start")), true, FVector2D(3.0f, 3.0f));
	SpawnBall();
}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ABallPawn::Shoot);
	PlayerInputComponent->BindAction("MoveForward", IE_Released, this, &ABallPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveTargetY", this, &ABallPawn::MoveTargetY);
	PlayerInputComponent->BindAxis("MoveTargetZ", this, &ABallPawn::MoveTargetZ);
}

//�f�o�b�O�p o�������ƌĂяo��
void ABallPawn::MoveForward()
{
	SetPosition();
}


//�{�[���𔭎˂�����
void ABallPawn::Shoot()
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("shoot")), true, FVector2D(3.0f, 3.0f));

	if (Ball)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Shoot")), true, FVector2D(3.0f, 3.0f));
		//FVector Direction = TargetRotation.Vector();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TargetDirection.ToString(), true, FVector2D(3.0f, 3.0f));

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (RootLocation - TargetDirection + FVector(0.0f, 0.0f, 0.0f)).ToString(), true, FVector2D(3.0f, 3.0f));
		Ball->ShootInDirection(TargetDirection);
	}
	

}

void ABallPawn::SpawnBall()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Ball = World->SpawnActor<ABall>(BallClass, ShootingPoint, FRotator(), Params);
		//ShootTarget = World->SpawnActor<AShootTarget>(ShootTargetClass, TargetDirection, FRotator(), Params);

		if (Ball)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Born")), true, FVector2D(3.0f, 3.0f));
		}
	}
}

//�}�E�X��X���ƃo�C���h���ăS�[�����ʂɑ΂��ĉ������̃x�N�g���̒l�̐ݒ�
void ABallPawn::MoveTargetY(float AxisValue)
{
	TargetDirection.Y += AxisValue;

	//Z�����������t�ɂ���
	Temp = RootLocation - TargetDirection;
	Temp.Z = -Temp.Z;
	ShootTargetMesh->SetRelativeLocation(Temp);
}
//�}�E�X�̂����ƃo�C���h���ăS�[�����ʂɑ΂��ďc�����̃x�N�g���̒l�̐ݒ�
void ABallPawn::MoveTargetZ(float AxisValue)
{
	TargetDirection.Z += AxisValue;
	
	//Z�����������t�ɂ���
	Temp = RootLocation - TargetDirection;
	Temp.Z = -Temp.Z;
	ShootTargetMesh->SetRelativeLocation(Temp);
}

//Ball�̈ʒu��Velocity�̏�����
void ABallPawn::SetPosition()
{
	TargetDirection = FVector(-500.0f, 0.0f, 154.0f);
	Ball->ProjectileMovementComponent->InitialSpeed = 2.0f;
	Ball->ProjectileMovementComponent->Velocity = FVector(0.0f, 0.0f, 0.0f);

	Ball->SetActorLocation(ShootingPoint);

}
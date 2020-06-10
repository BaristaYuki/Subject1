// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Dribbler.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include "Ball.h"

//////////////////////////////////////////////////////////////////////////
// ADribbler

ADribbler::ADribbler()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//GetCapsuleComponent()->SetCollisionProfileName(TEXT("OverlapBegin"));
	//GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ADribbler::OnCompHit);

	//コリジョンの設定とHItイベントのデリゲートに関数を追加
	CollisionMesh = nullptr;
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	//CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ADribbler::OnOverlapBegin);
	//CollisionMesh->OnComponentHit.AddDynamic(this, &ADribbler::OnCompHit);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	bTouched = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ADribbler::BeginPlay()
{
	Super::BeginPlay();
	SpawnBall();
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ADribbler::OnOverlapBegin);
	CollisionMesh->OnComponentHit.AddDynamic(this, &ADribbler::OnCompHit);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Begin")), true, FVector2D(3.0f, 3.0f));
}

void ADribbler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIfHit)
	{
		Ball->Dribble(Direction);
		bIfHit = false;
	}
}

void ADribbler::SpawnBall()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Ball = World->SpawnActor<ABall>(BallClass, GetActorLocation() + FVector(110.0f, 0.0f, 0.0f), FRotator(), Params);
		
	}
}

void ADribbler::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward2", this, &ADribbler::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADribbler::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADribbler::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADribbler::LookUpAtRate);
}

//Ballとだけoverlapした場合ドリブルする
void ADribbler::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	FName tag = "Ball";
	//FName Tag = Hit->ComponentTags[0];
	//FString Str = Tag.ToString();

	if (OtherComp->ComponentHasTag(tag))
	{
		bTouched = true;
		Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		// overlapしたらカメラの方向からベクトル取得
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);


		bIfHit = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("DribblerTagTrue")), true, FVector2D(3.0f, 3.0f));
	}
}

void ADribbler::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void ADribbler::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADribbler::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADribbler::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (!bTouched) {
			Rotation = Controller->GetControlRotation();
			FRotator YawRotation(0, Rotation.Yaw, 0);
			// overlapしたらカメラの方向からベクトル取得
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			AddMovementInput(Direction, Value);
		}
		else {
			AddMovementInput(Direction, Value);
		}
	}
}

void ADribbler::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);

		bTouched = false;
	}
}



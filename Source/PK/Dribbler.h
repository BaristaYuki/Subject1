// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

//Dribblerと書いてあるがドリブルだけするクラスではない。１選手のクラス　（名前変えたい。。）
#pragma once

#include "Delegate.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dribbler.generated.h"

//DECLARE_MULTICAST_DELEGATE(FPASSDispather);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPASSDispather);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitDispather);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPassDispather, float, myindex);

UCLASS()
class ADribbler : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	    class UBoxComponent* CollisionMesh;

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	ADribbler();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AController* OurController;

	bool bIfHit;


protected:
	
	bool bPosseceBall;

	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	//蹴りだしたボールに向かうためのフラグ
	bool bTouched;

	//デリゲートの通知も行う関数
	UFUNCTION()
	void ShortPass();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	UPROPERTY(EditDefaultsOnly, Category = Ball)
	TSubclassOf<class ABall>BallClass;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	bool GetbIsPossece();

	UFUNCTION()
	void SetIsPossece(bool b);

	UPROPERTY(BlueprintAssignable)
	FPASSDispather PassDispather;

	UPROPERTY(BlueprintAssignable)
	FHitDispather HitDispather;

	UFUNCTION()
	void SetDirection();

	ABall* Ball;

	FRotator D_Rotation;
	FRotator Camera_Rotation;

	FRotator Rotation;
	FRotator YawRotation;
	FVector Direction;

	FVector Dir;
};


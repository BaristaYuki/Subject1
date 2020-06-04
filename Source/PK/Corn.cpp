// Fill out your copyright notice in the Description page of Project Settings.


#include "Corn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ACorn::ACorn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(RootComponent);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->OnComponentHit.AddDynamic(this, &ACorn::OnCompHit);

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	ParticleSystemComponent->SetupAttachment(StaticMesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		ParticleSystemComponent->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void ACorn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACorn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACorn::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Coorn")), true, FVector2D(3.0f, 3.0f));
}


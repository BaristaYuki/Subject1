// Fill out your copyright notice in the Description page of Project Settings.


#include "UMGController.h"

void AUMGController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());

}
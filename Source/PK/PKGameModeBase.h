// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PKGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PK_API APKGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    /** Remove the current menu widget and create a new one from the specified class, if provided. (���݂̃��j���[�E�B�W�F�b�g����菜���A�w�肳�ꂽ�N���X������΂�������V�������̂��쐬���܂�) */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
    /** Called when the game starts. (�Q�[���J�n���ɌĂяo����܂�) */
    virtual void BeginPlay() override;

    /** The widget class we will use as our menu when the game starts. (�Q�[���J�n���Ƀ��j���[�Ƃ��Ďg�p����E�B�W�F�b�g �N���X�ł�) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> StartingWidgetClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> KikkerWidgetClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> KeeperWidgetClass;

    /** The widget instance that we are using as our menu.  (���j���[�Ƃ��Ďg�p����E�B�W�F�b�g �C���X�^���X�ł�) */
    UPROPERTY()
        UUserWidget* CurrentWidget;
	
};

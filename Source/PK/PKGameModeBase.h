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
    /** Remove the current menu widget and create a new one from the specified class, if provided. (現在のメニューウィジェットを取り除き、指定されたクラスがあればそこから新しいものを作成します) */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
    /** Called when the game starts. (ゲーム開始時に呼び出されます) */
    virtual void BeginPlay() override;

    /** The widget class we will use as our menu when the game starts. (ゲーム開始時にメニューとして使用するウィジェット クラスです) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> StartingWidgetClass;

    /** The widget instance that we are using as our menu.  (メニューとして使用するウィジェット インスタンスです) */
    UPROPERTY()
        UUserWidget* CurrentWidget;
	
};

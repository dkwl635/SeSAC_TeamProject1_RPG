// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DungeonGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API ADungeonGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText GameStateText;

public:
	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UFUNCTION(BlueprintCallable)
	void GameClear();
};

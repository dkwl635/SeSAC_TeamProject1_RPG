// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DungeonGameStateBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPOEGameState : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	GameReady UMETA(DisplayName = "GameReady"),
	GameIng UMETA(DisplayName = "GameIng"),
	GameOver UMETA(DisplayName = "GameOver"),
	GameClear UMETA(DisplayName = "GameClear"),
	

};

UCLASS()
class TEAMPROJECT_POEKOR_API ADungeonGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText GameStateText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EPOEGameState CurGameState = EPOEGameState::NONE;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeGameState(EPOEGameState NewGameState);
protected:

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void GameOver();

	UFUNCTION(BlueprintCallable)
	void GameClear();

	

};

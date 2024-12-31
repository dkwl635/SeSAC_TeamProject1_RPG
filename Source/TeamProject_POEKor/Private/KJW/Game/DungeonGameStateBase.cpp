// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/Game/DungeonGameStateBase.h"

void ADungeonGameStateBase::StartGame()
{
	GameStateText = FText::FromString("GameStart");
	CurGameState = EPOEGameState::GameIng;
}

void ADungeonGameStateBase::GameOver()
{
	GameStateText = FText::FromString("GameOver");
	CurGameState = EPOEGameState::GameOver;
}

void ADungeonGameStateBase::GameClear()
{
	GameStateText = FText::FromString("GameClear");
	CurGameState = EPOEGameState::GameClear;
}

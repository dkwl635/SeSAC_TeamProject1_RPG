// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/Game/DungeonGameStateBase.h"

void ADungeonGameStateBase::StartGame()
{
	GameStateText = FText::FromString("GameStart");
}

void ADungeonGameStateBase::GameOver()
{
	GameStateText = FText::FromString("GameOver");
}

void ADungeonGameStateBase::GameClear()
{
	GameStateText = FText::FromString("GameClear");
}

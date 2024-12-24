// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/Game/DungeonGameStateBase.h"

void ADungeonGameStateBase::StartGame()
{
	GameStateText = NSLOCTEXT("GameState", "GameStart", "GameStart");
}

void ADungeonGameStateBase::GameOver()
{
	GameStateText = NSLOCTEXT("GameState", "GaemOver", "GaemOver");
}

void ADungeonGameStateBase::GameClear()
{
	GameStateText = NSLOCTEXT("GameState", "GameClear", "GameClear");
}

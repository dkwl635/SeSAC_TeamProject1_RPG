// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/ActorComponent/StatsActorComponent.h"

// Sets default values for this component's properties
UStatsActorComponent::UStatsActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UStatsActorComponent::BeginPlay()
{
	Super::BeginPlay();

	Hp = MaxHp;
	// ...
}



float UStatsActorComponent::AddMaxHp(float AddValue)
{
	MaxHp += AddValue;

	return MaxHp;
}

float UStatsActorComponent::AddHp(float AddValue)
{
	Hp += AddValue;
	return Hp;
}

float UStatsActorComponent::AddAtk(float AddValue)
{
	Atk += AddValue;
	return Atk;
}

float UStatsActorComponent::AddDef(float AddValue)
{
	Def += AddValue;
	return Def;
}



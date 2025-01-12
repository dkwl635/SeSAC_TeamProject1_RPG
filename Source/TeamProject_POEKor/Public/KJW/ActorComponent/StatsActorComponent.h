// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMPROJECT_POEKOR_API UStatsActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere ,Category = "Stats")
	float MaxHp = 100;
	UPROPERTY(EditAnywhere ,Category = "Stats")
	float Hp = 100;
	UPROPERTY(EditAnywhere ,Category = "Stats")
	float Atk = 10;
	UPROPERTY(EditAnywhere ,Category = "Stats")
	float Def = 1;

public:
	UFUNCTION(BlueprintCallable)
	float GetMaxHp() {return MaxHp; }

	UFUNCTION(BlueprintCallable)
	float GetHp() {return Hp; }

	UFUNCTION(BlueprintCallable)
	float GetAtk() {return Atk; }

	UFUNCTION(BlueprintCallable)
	float GetDef() {return Def; }

	UFUNCTION(BlueprintCallable)
	float AddMaxHp(float AddValue);

	UFUNCTION(BlueprintCallable)
	float AddHp(float AddValue);

	
		UFUNCTION(BlueprintCallable)
	float AddAtk(float AddValue);

			UFUNCTION(BlueprintCallable)
	float AddDef(float AddValue);
};

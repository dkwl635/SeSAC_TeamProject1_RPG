// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHpBar.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TEAMPROJECT_POEKOR_API UEnemyHpBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite , meta =(Bindwidget))
	class UProgressBar* Hpbar;

public:
	UFUNCTION(BlueprintCallable)
	void SetHpBarPercent(float percent);

public :
	UPROPERTY(EditAnywhere)
	float TempHpPercent = 1.0f;
	UPROPERTY(EditAnywhere)
	float CurrentHpPercent = 1.0f;

	FTimerHandle HpTimeHandle;

	UFUNCTION()
	void HpBarLerp();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossUI.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UBossUI : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	class UTextBlock* TextBlock_Hp;
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	class UTextBlock* TextBlock_MaxHp;
	
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	class UProgressBar* ProgressBar_Hp;
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	class UProgressBar* ProgressBar_HpShadow;
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	class UProgressBar* ProgressBar_Stun;




private:
	UPROPERTY()
	class ABoss* boss;



public:
	UFUNCTION(BlueprintCallable)
	void SetBoss(ABoss* NewBoss);

private:
	UFUNCTION()
	void SetHpBar();
	UFUNCTION()
	void SetStunBar();

public :

	float TempHpPercent = 1.0f;
	float CurrentHpPercent = 1.0f;
	float TempHpShadowPercent = 1.0f;

	FTimerHandle HpTimeHandle;
	FTimerHandle HpShadowTimeHandle;
	FTimerHandle StunTimeHandle;

	float CurrentStunPercent = 0.f;
	float TempStunPercent = 0.f;


	UFUNCTION()
	void HpBarLerp();
	UFUNCTION()
	void HpBarShadowLerp();
	UFUNCTION()
	void StunBarLerp();
};

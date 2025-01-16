// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBottom.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
class UProgressBar;
UCLASS()
class TEAMPROJECT_POEKOR_API UUIBottom : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void InitUI();

protected:

	UPROPERTY()
	class UStatsActorComponent* Stats;
	UPROPERTY()
	class UUIPlayerMain* MainUI;

public:
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	UButton* Button_Eq;
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	UButton* Button_Inven;
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	UTextBlock* TextBlock_Hp;
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	UTextBlock* TextBlock_MaxHp;
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	UProgressBar* ProgressBar_Hp;

public:
	void SetMainUI(UUIPlayerMain* NewMainUI);

	
private:
	void ToggleButton(enum class EUIType UIType);
	UFUNCTION()
	void TogglePlayerInfo();
	UFUNCTION()
	void ToggleInven();

	
	void SetHpOrb();
	
public:
	UPROPERTY(EditAnywhere)
	float TempHpPercent = 1.0f;
	UPROPERTY(EditAnywhere)
	float CurrentHpPercent = 1.0f;

	float hpDelay = 0.f;
	FTimerHandle HpTimeHandle;
	UFUNCTION()
	void HpBarLerp();
	UFUNCTION()
	void ShadowHpBarLerp();

};

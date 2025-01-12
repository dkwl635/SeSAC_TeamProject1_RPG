// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJW/UI/UIBase.h"
#include "UIPlayerInfo.generated.h"


class UGearSlot;
class UTextBlock;
/**

 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UUIPlayerInfo : public UUIBase
{
	GENERATED_BODY()
	
public:
		UUIPlayerInfo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGearSlot* WBP_GearWeaponSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGearSlot* WBP_GearHatSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UGearSlot* WBP_GearArmorSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock_MaxHpValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock_AtkValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock_MaxDefValue;

protected:
	virtual void InitUI() override;

public:
	virtual void ShowUI() override;
	virtual void HideUI() override;

protected:
	void SetGearSlots();
	void SetStats();

	UFUNCTION()
	void ChangeGearEvent();
protected:
	UPROPERTY()
	class UInventoryComponent* PlayerInven;
	UPROPERTY()
	class UStatsActorComponent* StatsComponent;
};

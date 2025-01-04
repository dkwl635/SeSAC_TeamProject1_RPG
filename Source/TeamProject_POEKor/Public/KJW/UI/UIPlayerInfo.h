// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJW/UI/UIBase.h"
#include "UIPlayerInfo.generated.h"

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
	class UGearSlot* WBP_GearWeaponSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UGearSlot* WBP_GearHatSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UGearSlot* WBP_GearArmorSlot;

protected:
	virtual void InitUI() override;

public:
	virtual void ShowUI() override;
	virtual void HideUI() override;

protected:
	UFUNCTION()
	void SetGearSlots();

protected:
	class UInventoryComponent* PlayerInven;

};

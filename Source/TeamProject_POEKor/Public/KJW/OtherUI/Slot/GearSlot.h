// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJW/OtherUI/Slot/UISlotBase.h"
#include "KJW/ItemData/ItemDataTable.h"
#include "GearSlot.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UGearSlot : public UUISlotBase
{
	GENERATED_BODY()

public:
	UGearSlot();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotBG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* GearIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotHoverFrame;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGearType GearType = EGearType::NONE;

public:
	void SetSlot(const class UItemBase* ItemBase);
	void OnOffHoverImage(bool bOnHover);

public:
	virtual	bool IsMoveSlot() override;
	virtual bool IsEmptySlot() override;
	
};

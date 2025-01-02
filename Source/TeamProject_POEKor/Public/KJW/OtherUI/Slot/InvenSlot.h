// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJW/OtherUI/Slot/UISlotBase.h"
#include "InvenSlot.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UInvenSlot : public UUISlotBase
{
	GENERATED_BODY()
public:
	UInvenSlot();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotBG;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotHoverFrame;

protected:
	UPROPERTY(VisibleAnywhere)
	int32 SlotIndex = 0;

public:
	void SetSlotIndex(int32 NewSlotIndex);
	void SetSlot(class UItemBase* ItemBase);
	
	void OnOffHoverImage(bool bOnHover);
};

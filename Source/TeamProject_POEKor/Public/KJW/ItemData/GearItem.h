// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJW/ItemData/ItemBase.h"
#include "GearItem.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UGearItem : public UItemBase
{
	GENERATED_BODY()
public:
	virtual void InitializeItem(const FItemData& Data, int32 InitQuantity = 1) override;
	void SetGearStatus();
	
protected:
	FGearStatus GearStatus;

public:
	EGearType GetGearType(){ return GearStatus.GearType; }
	int32 GetAddStatus() { return GearStatus.AddState; }
};

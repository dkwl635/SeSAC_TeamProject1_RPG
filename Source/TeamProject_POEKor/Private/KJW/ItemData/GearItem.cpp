// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/ItemData/GearItem.h"


void UGearItem::InitializeItem(const FItemData& Data, int32 InitQuantity)
{
	UItemBase::InitializeItem(Data, InitQuantity);
	SetGearStatus();
}

void UGearItem::SetGearStatus()
{
	FGearStatus* NewGearStatus = ItemData.StatusData.DataTable->FindRow<FGearStatus>(ItemData.StatusData.RowName, TEXT(""));
	GearStatus.Copy(*NewGearStatus);
	

}

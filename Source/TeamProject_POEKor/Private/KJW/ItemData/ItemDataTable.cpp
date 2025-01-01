// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/ItemData/ItemDataTable.h"

FItemData& FItemData::operator=(const FItemData& Other)
{
    if (this != &Other)
    {
        UniqueID = Other.UniqueID;
        ItemType = Other.ItemType;
        ItemGrade = Other.ItemGrade;
        MaxQuantity = Other.MaxQuantity;
        ItemName = Other.ItemName;
        ItemDesc = Other.ItemDesc;
        StatusData = Other.StatusData;
    }

	return *this;
	
}

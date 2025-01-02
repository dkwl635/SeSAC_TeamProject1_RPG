// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/ItemData/ItemDataTable.h"


void FItemData::Copy(FItemData& OtherItem)
{
    UniqueID = OtherItem.UniqueID;
    ItemType = OtherItem.ItemType;
    ItemGrade = OtherItem.ItemGrade;
    MaxQuantity = OtherItem.MaxQuantity;
    
    ItemName = OtherItem.ItemName;
    ItemDesc = OtherItem.ItemDesc;
    ItemIcon = OtherItem.ItemIcon;

    StatusData = OtherItem.StatusData;


}

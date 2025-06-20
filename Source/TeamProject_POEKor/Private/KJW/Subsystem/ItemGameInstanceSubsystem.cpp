// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/Subsystem/ItemGameInstanceSubsystem.h"
#include "KJW/Actor/Item/DropItem.h"
#include "KJW/UI/Item/ItemInfoBox.h"

void UItemGameInstanceSubsystem::InitData(UWorld* World)
{
    TArray<FName> RowNames = ItemDataTable->GetRowNames();
    for (int32 i = 0; i < RowNames.Num(); i++)
    {
        FItemData* RowData = ItemDataTable->FindRow<FItemData>(RowNames[i], TEXT(""));
        ItemTableFindRowName.Add(RowData->UniqueID, RowNames[i]);     
    }
}

UItemBase* UItemGameInstanceSubsystem::GetNewItem(int32 UniqueID, int32 CurrentQuantity)
{
    FItemData NewItemData;
    if (GetItemData(NewItemData, UniqueID))
    {
        UItemBase* NewItem = NewObject<UItemBase>();
        if (NewItemData.ItemType == EItemType::Gear)
        {
            NewItem = NewObject<UGearItem>();
        }
        else
        {
            NewItem = NewObject<UItemBase>();
        }

       
        NewItem->InitializeItem(NewItemData, CurrentQuantity);
        //UE_LOG(LogTemp, Warning, TEXT("NewItem %s"), *NewItem->GetItemName().ToString());
        return NewItem;
    }


    return nullptr;
}

ADropItem* UItemGameInstanceSubsystem::GetNewDropItem(int32 UniqueID, int32 CurrentQuantity, AActor* Owner)
{
    if (!Owner) { return nullptr; }

    FVector SpawnLocation = Owner->GetActorLocation();
    FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

    ADropItem* DropItem = Owner->GetWorld()->SpawnActor<ADropItem>(DropItemClass , SpawnLocation , SpawnRotation);

    UItemBase* ItemBase = GetNewItem(UniqueID, CurrentQuantity);
    DropItem->SetDropItem(ItemBase);


    return DropItem;
}

bool UItemGameInstanceSubsystem::GetItemData(FItemData& RefItemData, int32 UniqueID)
{
    if (!ItemDataTable) { return false; }

   FName rowName = GetItemTableRowName(UniqueID);
   if (rowName.IsEqual("")) { return false; }

   FItemData* FindItemData = ItemDataTable->FindRow<FItemData>(rowName , TEXT(""));
   RefItemData = *FindItemData;

   return true;
}

FName UItemGameInstanceSubsystem::GetItemTableRowName(int32 UniqueID)
{
    FName rowName = "";
    if (ItemTableFindRowName.Contains(UniqueID))
    {
        rowName = ItemTableFindRowName[UniqueID];
    }
    else
    {
        TArray<FName> RowNames = ItemDataTable->GetRowNames();
        for (int32 i = 0; i < RowNames.Num(); i++)
        {
            FItemData* RowData = ItemDataTable->FindRow<FItemData>(RowNames[i], TEXT(""));
            if (RowData->UniqueID == UniqueID)
            {
                rowName = RowNames[i];
                ItemTableFindRowName.Add(UniqueID, rowName);
            }
        }
    }


    return rowName;
}

void UItemGameInstanceSubsystem::SetItemInfoBox(UItemInfoBox* NewItemInfoBox)
{
    ItemInfoBox = NewItemInfoBox;
}

void UItemGameInstanceSubsystem::ShowItemInfoBox(UItemBase* Item)
{
    if (ItemInfoBox.IsValid())
    {
        ItemInfoBox->SetItemInfoBox(Item);
    }
}

void UItemGameInstanceSubsystem::HideItemInfoBox()
{
    if (ItemInfoBox.IsValid())
    {
        ItemInfoBox->HideInfoBox();
    }
}

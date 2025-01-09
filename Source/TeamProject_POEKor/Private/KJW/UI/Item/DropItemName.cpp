// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/UI/Item/DropItemName.h"
#include "KJW/Actor/Item/DropItem.h"
#include "KJW/ItemData/ItemBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UDropItemName::NativeConstruct()
{
	Button_Item->OnClicked.AddDynamic(this, &ThisClass::DropItemButtonAction);
}

void UDropItemName::DropItemButtonAction()
{
	if (DropItem)
	{
		DropItem->AddItem();
	}
}

void UDropItemName::SetDropItem(ADropItem* NewDropItem)
{
	DropItem = NewDropItem;
	if (DropItem && DropItem->Item)
	{
		FText ItemNameText = DropItem->Item->GetItemName();
		TextBlock_ItemName->SetText((ItemNameText));


		EItemGrade ItemGrade = DropItem->Item->GetItemGrade();
		
		switch (ItemGrade)
		{
		case EItemGrade::NONE:
			break;
		case EItemGrade::Common:
			TextBlock_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor::White));
			break;
		case EItemGrade::Uncommon:
			TextBlock_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
			break;
		case EItemGrade::Rare:
			TextBlock_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
			break;
		case EItemGrade::Legendary:
			break;
		default:
			break;
		}

	}

}

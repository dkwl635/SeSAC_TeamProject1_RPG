// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/OtherUI/Slot/InvenSlot.h"
#include "KJW/ItemData/ItemBase.h"

#include "Components/Image.h"

UInvenSlot::UInvenSlot()
{
	SlotType = EUISlotType::Inven;
}

void UInvenSlot::SetSlotIndex(int32 NewSlotIndex)
{
	SlotIndex = NewSlotIndex;
}

void UInvenSlot::SetSlot(UItemBase* ItemBase)
{
	if (ItemBase)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
		ItemEffect->SetVisibility(ESlateVisibility::Visible);


		ItemIcon->SetBrushFromTexture(ItemBase->GetItemIcon());

	}
	else
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		ItemEffect->SetVisibility(ESlateVisibility::Hidden);

	}
}

void UInvenSlot::OnOffHoverImage(bool bOnHover)
{
	if (bOnHover)
	{
		SlotHoverFrame->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SlotHoverFrame->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UInvenSlot::IsMoveSlot()
{
	return ItemIcon->GetVisibility() == ESlateVisibility::Visible;
	
}

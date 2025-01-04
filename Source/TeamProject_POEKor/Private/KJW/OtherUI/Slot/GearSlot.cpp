// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/OtherUI/Slot/GearSlot.h"
#include "KJW/ItemData/ItemBase.h"

#include "Components/Image.h"

UGearSlot::UGearSlot()
{
	SlotType = EUISlotType::Gear;
}

void UGearSlot::SetSlot(const UItemBase* ItemBase)
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

void UGearSlot::OnOffHoverImage(bool bOnHover)
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

bool UGearSlot::IsMoveSlot()
{
	return ItemIcon->GetVisibility() == ESlateVisibility::Visible;
}

bool UGearSlot::IsEmptySlot()
{
	return ItemIcon->GetVisibility() ==ESlateVisibility::Hidden;
}

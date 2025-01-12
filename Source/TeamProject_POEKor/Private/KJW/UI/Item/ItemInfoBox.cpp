// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/UI/Item/ItemInfoBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "KJW/ItemData/ItemBase.h"
#include "KJW/Subsystem/ItemGameInstanceSubsystem.h"

void UItemInfoBox::NativeConstruct()
{
	Super::NativeConstruct();

	UItemGameInstanceSubsystem* ItemInstance = GetGameInstance()->GetSubsystem<UItemGameInstanceSubsystem>();
	if (ItemInstance)
	{
		ItemInstance->SetItemInfoBox(this);
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UItemInfoBox::SetItemInfoBox(UItemBase* Item)
{
	if (Item)
	{
		Image_Item->SetBrushFromTexture(Item->GetItemIcon());

		TextBlock_ItemName->SetText(Item->GetItemName());
		TextBlock_ItemDesc->SetText(Item->GetItemDesc());

		if (Item->GetItemGrade() == EItemGrade::Uncommon)
		{
			TextBlock_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
		}
		else if (Item->GetItemGrade() == EItemGrade::Rare)
		{
			TextBlock_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		}
		else
		{
			TextBlock_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		}

		
	}
	this->SetVisibility(ESlateVisibility::Visible);
}

void UItemInfoBox::HideInfoBox()
{
	
	this->SetVisibility(ESlateVisibility::Hidden);
}

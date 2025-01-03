// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/OtherUI/Slot/UISlotBase.h"

bool UUISlotBase::IsOnClickedSlot = false;
UUISlotBase* UUISlotBase::ClickedSlot = nullptr;

bool UUISlotBase::IsMoveSlot()
{
    return false;
}

bool UUISlotBase::IsShowParent()
{
    if (ParentUserWidget)
    {
        return ParentUserWidget->GetVisibility() == ESlateVisibility::Visible;
    }

    return false;
}

void UUISlotBase::SetParent(UUserWidget* NewParent)
{
    ParentUserWidget = NewParent;
}

void UUISlotBase::OnClickedSlot()
{
}

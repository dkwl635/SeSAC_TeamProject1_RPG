// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/OtherUI/Slot/UISlotBase.h"


bool UUISlotBase::IsMoveSlot()
{
    return false;
}

bool UUISlotBase::IsShowParent()
{
    UE_LOG(LogTemp, Warning, TEXT("IsShowParent ") );
    if (ParentUserWidget)
    {
        return ParentUserWidget->GetVisibility() == ESlateVisibility::Visible;
    }

    return false;
}

bool UUISlotBase::IsEmptySlot()
{
    return false;
}

void UUISlotBase::SetParent(UUserWidget* NewParent)
{
    ParentUserWidget = NewParent;
}

void UUISlotBase::OnClickedSlot()
{
}

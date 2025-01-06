// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/UI/UIBase.h"
#include "Components/CanvasPanelSlot.h"


void UUIBase::InitUI()
{
	
	
}

UCanvasPanelSlot* UUIBase::GetCanvasSlot()
{
	if (!CanvasSlot)
	{
		if (UCanvasPanelSlot* CurCanvasSlot = Cast<UCanvasPanelSlot>(Slot))
		{
			CanvasSlot = CurCanvasSlot;
		}
	}

	return CanvasSlot;
}

void UUIBase::ShowUI()
{
	if (bIsInit == false) { InitUI(); bIsInit = true; }
	this->SetVisibility(ESlateVisibility::Visible);

}

void UUIBase::RefreshUI()
{

}

void UUIBase::HideUI()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UUIBase::TopUI()
{
}

bool UUIBase::ToggleUI()
{
	if (this->GetVisibility() == ESlateVisibility::Hidden)
	{
		ShowUI();
		return false;
	}
	else
	{
		HideUI();
		return true;
	}

	
}

void UUIBase::SetZOrder(int32 NewZOrder)
{
	UCanvasPanelSlot* Canvas = GetCanvasSlot();
	if (!Canvas) { return; }

	Canvas->SetZOrder(NewZOrder);
}

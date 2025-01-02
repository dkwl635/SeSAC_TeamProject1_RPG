// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/UI/UIBase.h"

void UUIBase::InitUI()
{
}

void UUIBase::ShowUI()
{
	if (bIsInit == false) { InitUI(); bIsInit = true; }

}

void UUIBase::RefreshUI()
{
}

void UUIBase::HideUI()
{
}

void UUIBase::TopUI()
{
}

bool UUIBase::ToggleUI()
{
	if (this->GetVisibility() == ESlateVisibility::Hidden)
	{
		this->RemoveFromParent();
		return false;
	}
	else
	{
		this->AddToViewport();
		return true;
	}

	
}

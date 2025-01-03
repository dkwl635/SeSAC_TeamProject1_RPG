// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/UI/UIBase.h"

void UUIBase::InitUI()
{

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

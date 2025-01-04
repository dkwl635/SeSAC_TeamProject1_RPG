// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/UI/UIPlayerMain.h"
#include "KJW/UI/UIHeader.h"
#include "KJW/OtherUI/Slot/UISlotBase.h"
#include "Blueprint/WidgetTree.h"

void UUIPlayerMain::NativeConstruct()
{
	Super::NativeConstruct();


	if (!WidgetTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("WidgetTree is null!"));
		return;
	}

	TArray<UWidget*> AllWidgets;
	WidgetTree->GetAllWidgets(AllWidgets);

	
	for (UWidget* Widget : AllWidgets)
	{
		if (UUIBase* NewUI = Cast<UUIBase>(Widget))
		{
			EUIType UIType= NewUI->GetUIType();
			if (UIType == EUIType::NONE) { continue; }

			if (UIMap.Contains(UIType))
			{
				UE_LOG(LogTemp, Error, TEXT("Contains UIType"));
			}

			UIMap.Add(UIType, NewUI);
			NewUI->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	
}

void UUIPlayerMain::NativeDestruct()
{
	Super::NativeDestruct();

}

void UUIPlayerMain::ShowUI(EUIType UIType)
{
	if (UIMap.Contains(UIType))
	{
		UIMap[UIType]->ShowUI();
	}
}

void UUIPlayerMain::ToggleUI(EUIType UIType)
{
	if (UIMap.Contains(UIType))
	{
		UIMap[UIType]->ToggleUI();
	}
}

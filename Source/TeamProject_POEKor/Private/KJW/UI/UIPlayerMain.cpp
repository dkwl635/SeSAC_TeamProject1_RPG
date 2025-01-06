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
		
		if (UIList.Contains(UIMap[UIType]))
		{
			UIList.Remove(UIMap[UIType]);
		}

		if(!UIList.Contains(UIMap[UIType]))
		{
			UIList.Add(UIMap[UIType]);
		}

		UpdateZOrder();
	}
}

void UUIPlayerMain::HideUI(EUIType UIType)
{
	if (UIMap.Contains(UIType))
	{
		UIMap[UIType]->HideUI();

		if (UIList.Contains(UIMap[UIType]))
		{
			UIList.Remove(UIMap[UIType]);
		}

		UpdateZOrder();
	}
}

void UUIPlayerMain::ToggleUI(EUIType UIType)
{
	if (UIMap.Contains(UIType))
	{
		if (UIList.Contains(UIMap[UIType]))
		{
			UIList.Remove(UIMap[UIType]);
		}

		if (UIMap[UIType]->ToggleUI())
		{
			// True == On
			if (!UIList.Contains(UIMap[UIType]))
			{
				UIList.Add(UIMap[UIType]);
			}

		}
		else
		{
			//False == Off
		}

		UpdateZOrder();
	}
}

void UUIPlayerMain::UpdateZOrder()
{
	int32 ZOrder = PlayerUIZOredr;
	for (int i = 0; i < UIList.Num(); i++)
	{
		int32 UIZOreder = ZOrder + i;
		UIList[i]->SetZOrder(UIZOreder);

	}
}

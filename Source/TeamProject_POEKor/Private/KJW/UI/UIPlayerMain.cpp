// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/UI/UIPlayerMain.h"
#include "KJW/UI/UIHeader.h"

void UUIPlayerMain::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < InitUIGroup.Num(); i++)
	{
		EUIType UIType = InitUIGroup[i].UIType;
		TSubclassOf<UUIBase> UIBaseClass = InitUIGroup[i].UIClass;

		UUIBase* NewUI = CreateWidget<UUIBase>(GetOwningPlayer(), UIBaseClass);
		if (NewUI)
		{
			if (UIMap.Contains(UIType))
			{
				UE_LOG(LogTemp, Error, TEXT("Contains UIType"));
			}

			UIMap.Add(UIType, NewUI);		
		}
	}
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

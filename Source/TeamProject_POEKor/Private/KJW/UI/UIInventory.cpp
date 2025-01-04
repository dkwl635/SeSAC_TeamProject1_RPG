// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/UI/UIInventory.h"
#include "KJW/ActorComponent/InventoryComponent.h"
#include "KJW/OtherUI/Slot/InvenSlot.h"

#include "KJW/ItemData/ItemBase.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

UUIInventory::UUIInventory()
{
	UIType = EUIType::Inven;
}

void UUIInventory::InitUI()
{
	Super::InitUI();

	TArray<UWidget*> Slots =  SlotUniformGridPanel->GetAllChildren();
	for (int32 i = 0; i < Slots.Num(); i++)
	{
		int32 SlotIndex = i;
		UInvenSlot* InvenSlot = Cast<UInvenSlot>(Slots[i]);
		if (InvenSlot)
		{
			InvenSlot->SetSlotIndex(SlotIndex);
			InvenSlot->SetSlot(nullptr);
			InvenSlot->SetParent(this);
			InvenSlots.Add(InvenSlot);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), InvenSlots.Num());


	APawn* PlayerPawn =	GetOwningPlayer()->GetPawn();
	if (PlayerPawn)
	{
		UInventoryComponent* InvenComponent = PlayerPawn->GetComponentByClass<UInventoryComponent>();
		if (InvenComponent)
		{
			PlayerInven = InvenComponent;
			PlayerInven->OnInventoryChanged.AddDynamic(this, &ThisClass::SetInvenSlots);
			UE_LOG(LogTemp, Warning, TEXT("PlayerInven Yes"));
		}
	}
}

void UUIInventory::ShowUI()
{
	Super::ShowUI();

	for (int i = 0; i < InvenSlots.Num(); i++)
	{
		InvenSlots[i]->OnOffHoverImage(false);
	}

	SetInvenSlots();
}

void UUIInventory::HideUI()
{
	Super::HideUI();
}

void UUIInventory::SetInvenSlots()
{
	if (PlayerInven)
	{
		const TArray<UItemBase*>& Inven = PlayerInven->GetInven();
		for (int32 i = 0; i < PlayerInven->InventoryMax; i++)
		{
			if (i >= PlayerInven->InventoryMax) { break; }

			InvenSlots[i]->SetSlot(Inven[i]);
		}

	}
}


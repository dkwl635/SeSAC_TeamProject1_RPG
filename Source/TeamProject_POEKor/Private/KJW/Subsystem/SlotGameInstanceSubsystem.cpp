// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/Subsystem/SlotGameInstanceSubsystem.h"
#include "KJW/ActorComponent/InventoryComponent.h"
#include "KJW/OtherUI/Slot/UISlotHeader.h"
#include "KJW/ItemData/ItemHeader.h"
#include "KJW/ItemData/ItemDataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameViewportClient.h"
#include "Blueprint/UserWidget.h"

void USlotGameInstanceSubsystem::ClearClickSlot()
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	IsOnClickedSlot = false;
	ClickedSlot = nullptr;
	SlotWorld = nullptr;
}

void USlotGameInstanceSubsystem::SetNewClickSlot(UUISlotBase* NewClickedSlot)
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	IsOnClickedSlot = true;
	ClickedSlot = NewClickedSlot;
	SlotWorld = NewClickedSlot->GetWorld();
}



void USlotGameInstanceSubsystem::OnClikedSlot(UUISlotBase* NewClickedSlot)
{
	if (IsOnClickedSlot == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("NewClickedSlot"));
		if (!NewClickedSlot->IsMoveSlot()) { return; }

		SetNewClickSlot(NewClickedSlot);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherClickedSlot"));
		if (!ClickedSlot->IsShowParent())
		{
			ClearClickSlot();
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("ClickedSlot == NewClickedSlot"));
		if (ClickedSlot.Get() == NewClickedSlot)
		{
			ClearClickSlot();
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("MoveSlotEvent"));
		IsOnClickedSlot = false;

		//Do Move Event
		MoveSlotEvent(ClickedSlot.Get(), NewClickedSlot);

		ClearClickSlot();
	}

	

}

void USlotGameInstanceSubsystem::FailedMoveSlot()
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	ClearClickSlot();
}



void USlotGameInstanceSubsystem::MoveSlotEvent(UUISlotBase* FromSlot, UUISlotBase* ToSlot)
{
	EUISlotType fromSlotType = FromSlot->GetSlotType();
	EUISlotType toSlotType = ToSlot->GetSlotType();

	//Inven Item Swap
	if (fromSlotType == EUISlotType::Inven && toSlotType == EUISlotType::Inven)
	{
		if (!SlotWorld.IsValid()) { return; }

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(SlotWorld.Get(), 0);
		UInventoryComponent* Inven = PlayerController->GetPawn()->GetComponentByClass<UInventoryComponent>();
		if (!Inven) { return; }

		UUISlotBase* InvenBaseSlot = fromSlotType == EUISlotType::Inven ? FromSlot : ToSlot;
		UUISlotBase* GearBaseSlot = fromSlotType == EUISlotType::Gear ? FromSlot : ToSlot;
		
		UInvenSlot* fromInvenSlot = Cast<UInvenSlot>(FromSlot);
		UInvenSlot* toInvenSlot = Cast<UInvenSlot>(ToSlot);
		int32 fromIndex = fromInvenSlot->GetSlotIndex();
		int32 toIndex = toInvenSlot->GetSlotIndex();

		//Move Item
		if (toInvenSlot->IsEmptySlot())
		{
			UItemBase* MoveItem = Inven->GetInvenItem(fromIndex);
			Inven->ClearInvenItem(fromIndex);
			Inven->AddItem(MoveItem, toIndex);
		}
		//Swap Item
		else if (!toInvenSlot->IsEmptySlot())
		{
			UItemBase* ItemA = Inven->GetInvenItem(fromIndex);
			UItemBase* ItemB = Inven->GetInvenItem(toIndex);
			Inven->ClearInvenItem(fromIndex);
			Inven->ClearInvenItem(toIndex);
			Inven->AddItem(ItemA, toIndex);
			Inven->AddItem(ItemB, fromIndex);
		}

		

	}
	//Equip Item or UnEquip
	else if ((fromSlotType == EUISlotType::Inven && toSlotType == EUISlotType::Gear) ||
		(fromSlotType == EUISlotType::Gear && toSlotType == EUISlotType::Inven))
	{

		if (!SlotWorld.IsValid()) { return; }

		UUISlotBase* InvenBaseSlot = fromSlotType == EUISlotType::Inven ? FromSlot : ToSlot;
		UUISlotBase* GearBaseSlot = fromSlotType == EUISlotType::Gear ? FromSlot : ToSlot;

		UInvenSlot* InvenSlot = Cast<UInvenSlot>(InvenBaseSlot);
		UGearSlot* GearSlot = Cast<UGearSlot>(GearBaseSlot);


		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(SlotWorld.Get(), 0);
		UInventoryComponent* Inven = PlayerController->GetPawn()->GetComponentByClass<UInventoryComponent>();
		if (!Inven) { return; }

		//Equip
		if (GearSlot->IsEmptySlot())
		{
			EGearType EqType = GearSlot->GearType;
			int32 InvenIndex = InvenSlot->GetSlotIndex();
			UItemBase* EqItem = Inven->GetInvenItem(InvenIndex);

			if (EqItem->GetItemType() != EItemType::Gear) { return; }

			UGearItem* EqGearItem = Cast<UGearItem>(EqItem);
			if (!EqGearItem) { return; }
			if (EqGearItem->GetGearType() != EqType) { return; }

			Inven->ClearInvenItem(InvenIndex);
			Inven->EquipGear(EqType, EqItem);


		}
		//UnEquip
		else if (InvenSlot->IsEmptySlot())
		{
			EGearType EqType = GearSlot->GearType;
			int32 InvenIndex = InvenSlot->GetSlotIndex();
			UItemBase* UnEqItem = Inven->GetGearItem(EqType);

			Inven->UnEquipGear(EqType);
			Inven->AddItem(UnEqItem, InvenIndex);
		}
		//Gear Swap
		else if (!InvenSlot->IsEmptySlot() && !GearSlot->IsEmptySlot())
		{
			EGearType EqType = GearSlot->GearType;
			int32 InvenIndex = InvenSlot->GetSlotIndex();
			UItemBase* EqItem = Inven->GetInvenItem(InvenIndex);

			if (EqItem->GetItemType() != EItemType::Gear) { return; }

			UGearItem* EqGearItem = Cast<UGearItem>(EqItem);
			if (!EqGearItem) { return; }
			if (EqGearItem->GetGearType() != EqType) { return; }

			UItemBase* UnEqItem = Inven->GetGearItem(EqType);

			Inven->UnEquipGear(EqType);
			Inven->EquipGear(EqType, EqItem);
			Inven->AddItem(UnEqItem, InvenIndex);

		}
	}


}
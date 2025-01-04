// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/UI/UIPlayerInfo.h"
#include "KJW/ActorComponent/InventoryComponent.h"
#include "KJW/OtherUI/Slot/GearSlot.h"

#include "KJW/ItemData/ItemBase.h"
UUIPlayerInfo::UUIPlayerInfo()
{
	UIType = EUIType::PlayerInfo;
}

void UUIPlayerInfo::InitUI()
{
	Super::InitUI();

	APawn* PlayerPawn = GetOwningPlayer()->GetPawn();
	if (PlayerPawn)
	{
		UInventoryComponent* InvenComponent = PlayerPawn->GetComponentByClass<UInventoryComponent>();
		if (InvenComponent)
		{
			PlayerInven = InvenComponent;
			PlayerInven->OnGearChanged.AddDynamic(this, &ThisClass::SetGearSlots);
			UE_LOG(LogTemp, Warning, TEXT("UUIPlayerInfo::PlayerInven Yes"));
		}
	}
	WBP_GearWeaponSlot->SetParent(this);
	WBP_GearHapSlot->SetParent(this);
	WBP_GearArmorSlot->SetParent(this);


}

void UUIPlayerInfo::ShowUI()
{
	Super::ShowUI();
	
	SetGearSlots();
}

void UUIPlayerInfo::HideUI()
{
	Super::HideUI();
}

void UUIPlayerInfo::SetGearSlots()
{
	if (PlayerInven)
	{
		WBP_GearWeaponSlot->SetSlot(PlayerInven->GetGearItem(EGearType::Weapon));
		WBP_GearHapSlot->SetSlot(PlayerInven->GetGearItem(EGearType::Hat));
		WBP_GearArmorSlot->SetSlot(PlayerInven->GetGearItem(EGearType::Armor));

	}
}

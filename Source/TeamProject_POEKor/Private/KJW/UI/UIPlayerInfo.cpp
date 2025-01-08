// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/UI/UIPlayerInfo.h"
#include "KJW/ActorComponent/InventoryComponent.h"
#include "KJW/ActorComponent/StatsActorComponent.h"
#include "KJW/OtherUI/Slot/GearSlot.h"
#include "KJW/ItemData/ItemBase.h"

#include "Components/TextBlock.h"

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
			PlayerInven->OnGearChanged.AddDynamic(this, &ThisClass::ChangeGearEvent);
			UE_LOG(LogTemp, Warning, TEXT("UUIPlayerInfo::PlayerInven Yes"));
		}
		UStatsActorComponent* StatsActorComponent = PlayerPawn->GetComponentByClass<UStatsActorComponent>();
		if (StatsActorComponent)
		{
			StatsComponent = StatsActorComponent;

		}
	}
	WBP_GearWeaponSlot->SetParent(this);
	WBP_GearWeaponSlot->GearType = EGearType::Weapon;
	WBP_GearHatSlot->SetParent(this);
	WBP_GearHatSlot->GearType = EGearType::Hat;
	WBP_GearArmorSlot->SetParent(this);
	WBP_GearArmorSlot->GearType = EGearType::Armor;

}

void UUIPlayerInfo::ShowUI()
{
	Super::ShowUI();
	
	SetGearSlots();
	SetStats();
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
		WBP_GearHatSlot->SetSlot(PlayerInven->GetGearItem(EGearType::Hat));
		WBP_GearArmorSlot->SetSlot(PlayerInven->GetGearItem(EGearType::Armor));

	}
}

void UUIPlayerInfo::SetStats()
{
	if (StatsComponent)
	{
		float MaxHp = StatsComponent->GetMaxHp();
		float Atk = StatsComponent->GetAtk();
		float Def = StatsComponent->GetDef();

		TextBlock_MaxHpValue->SetText(FText::AsNumber(MaxHp , 0));
		TextBlock_AtkValue->SetText(FText::AsNumber(Atk, 0));
		TextBlock_MaxDefValue->SetText(FText::AsNumber(Def, 0));
	}
}

void UUIPlayerInfo::ChangeGearEvent()
{
	SetGearSlots();
	SetStats();
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/ActorComponent/InventoryComponent.h"
#include "KJW/ItemData/ItemHeader.h"
#include "KJW/ActorComponent/StatsActorComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::InitInventory()
{
	Inven.Init(nullptr, InventoryMax);

	PlayerEqGears.Add(EGearType::Weapon , nullptr);
	PlayerEqGears.Add(EGearType::Hat , nullptr);
	PlayerEqGears.Add(EGearType::Armor , nullptr);
}

void UInventoryComponent::AddItem(UItemBase* NewItemBase)
{
	for (int32 i = 0; i < InventoryMax; i++)
	{
		if (Inven[i] == nullptr)
		{
			Inven[i] = NewItemBase;
			break;
		}
	}

	//Inven.Add(NewItemBase);

	if (OnInventoryChanged.IsBound())
	{	
		OnInventoryChanged.Broadcast();
	}

}

void UInventoryComponent::AddItem(UItemBase* NewItemBase, int32 InvenIndex)
{
	if (InvenIndex < 0 || InvenIndex >= InventoryMax) { return; }
	Inven[InvenIndex] = NewItemBase;


	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast();
	}
}

TArray<class UItemBase*>& UInventoryComponent::GetInven() 
{
	return Inven;
}

UItemBase* UInventoryComponent::GetInvenItem(int32 InvenIndex)
{
	if (InvenIndex < 0 || InvenIndex >= InventoryMax) { return nullptr; }
	return Inven[InvenIndex];
}

UItemBase* UInventoryComponent::GetGearItem(EGearType GearType)
{
	if (PlayerEqGears.Contains(GearType))
	{
		return PlayerEqGears[GearType];
	}
	return nullptr;
}

void UInventoryComponent::ClearInvenItem(int32 InvenIndex)
{
	if (InvenIndex < 0 || InvenIndex >= InventoryMax) { return; }

	Inven[InvenIndex] = nullptr;


	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast();
	}
}

void UInventoryComponent::EquipGear(EGearType GearType, UItemBase* GearItem)
{
	if (!PlayerEqGears.Contains(GearType)){return;}

	PlayerEqGears[GearType] = GearItem;
	SetGearStats(GearItem , true);

	if (OnGearChanged.IsBound())
	{
		OnGearChanged.Broadcast();
	}
}

void UInventoryComponent::UnEquipGear(EGearType GearType)
{
	if (!PlayerEqGears.Contains(GearType)) { return; }
	SetGearStats(PlayerEqGears[GearType], false);
	PlayerEqGears[GearType] = nullptr;

	if (OnGearChanged.IsBound())
	{
		OnGearChanged.Broadcast();
	}
}

void UInventoryComponent::SetGearStats(UItemBase* GearItem , bool bAddstats)
{
	if (!StatsComponent) { return; }

	UGearItem* GearData = Cast<UGearItem>(GearItem);
	if (!GearData) { return; }

	EGearType GearType = GearData->GetGearType();
	float AddValueRate = bAddstats ? 1.f : -1.f;
	float AddValue = GearData->GetAddStatus() * AddValueRate;
	if (GearType == EGearType::Weapon)
	{
		StatsComponent->AddAtk(AddValue);
	}
	else if (GearType == EGearType::Hat)
	{
		StatsComponent->AddDef(AddValue);
	}
	else if (GearType == EGearType::Armor)
	{
		StatsComponent->AddMaxHp(AddValue);
	}



}

void UInventoryComponent::SetStatsComponent(UStatsActorComponent* NewStatsComponent)
{
	StatsComponent = NewStatsComponent;
}


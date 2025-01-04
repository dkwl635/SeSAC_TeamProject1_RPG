// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/ActorComponent/InventoryComponent.h"
#include "KJW/ItemData/ItemHeader.h"

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

const TArray<class UItemBase*>& UInventoryComponent::GetInven() 
{
	return Inven;
}

UItemBase* const UInventoryComponent::GetInvenItem(int32 InvenIndex)
{
	if (InvenIndex < 0 || InvenIndex >= InventoryMax) { return nullptr; }
	return Inven[InvenIndex];
}

UItemBase* const UInventoryComponent::GetGearItem(EGearType GearType)
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
}

void UInventoryComponent::EquipGear(EGearType GearType, UItemBase* GearItem)
{
	if (!PlayerEqGears.Contains(GearType)){return;}

	PlayerEqGears[GearType] = GearItem;
}

void UInventoryComponent::UnEquipGear(EGearType GearType)
{
	if (!PlayerEqGears.Contains(GearType)) { return; }

	PlayerEqGears[GearType] = nullptr;
}


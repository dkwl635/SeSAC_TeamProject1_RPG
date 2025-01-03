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


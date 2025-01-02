// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/Actor/Item/DropItem.h"
#include "KJW/ActorComponent/InventoryComponent.h"

// Sets default values
ADropItem::ADropItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADropItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropItem::OnCharacterOverlap(AActor* OtherActor)
{
	UInventoryComponent* Inven = OtherActor->GetComponentByClass<UInventoryComponent>();
	if (Inven)
	{
		if (Item)
		{
		Inven->AddItem(Item);
		}
	}

	Destroy();
}


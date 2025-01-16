// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/Actor/Item/DropItem.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "KJW/ActorComponent/InventoryComponent.h"
#include "KJW/UI/Item/DropItemName.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ADropItem::ADropItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	ItemBeamComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ItemBeamComp"));

	SetRootComponent(SphereComp);
	WidgetComp->SetupAttachment(SphereComp);
	ItemBeamComp->SetupAttachment(RootComponent);
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

void ADropItem::SetDropItem(UItemBase* NewItem)
{
	Item = NewItem;
	if (!Item) return;

	if (WidgetComp->GetWidget())
	{
		UDropItemName* DropItemName = Cast<UDropItemName>(WidgetComp->GetWidget());
		if (DropItemName)
		{
			DropItemName->SetDropItem(this);
		}

		if (ItemBeamComp)
		{
			FColor MyColor;
			MyColor.A = 0;

			if (Item->GetItemGrade() == EItemGrade::Uncommon)
			{
				MyColor = FColor::Blue;
			}
			else if (Item->GetItemGrade() == EItemGrade::Rare)
			{
				MyColor = FColor::Yellow;
			}

			ItemBeamComp->SetNiagaraVariableLinearColor(TEXT("MyColor"), MyColor);
		}

	}
}

void ADropItem::AddItem()
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		UInventoryComponent* Inven = PlayerPawn->GetComponentByClass<UInventoryComponent>();
		if (Inven)
		{
			if (Item)
			{
				Inven->AddItem(Item);
			}
			Destroy();
		}
	}

	
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
	Destroy();
	}

}


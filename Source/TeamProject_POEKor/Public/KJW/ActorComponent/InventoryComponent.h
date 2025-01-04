// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KJW/ItemData/ItemDataTable.h"
#include "InventoryComponent.generated.h"


// No arguments
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAMPROJECT_POEKOR_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UPROPERTY(VisibleAnywhere)
	int32 InventoryMax = 20;
public:

	UFUNCTION(BlueprintCallable)
	void InitInventory();

protected :
	UPROPERTY(VisibleAnywhere, Instanced)
	TArray<class UItemBase*> Inven;

	UPROPERTY(VisibleAnywhere, Instanced)
	TMap<EGearType, class UItemBase*> PlayerEqGears;

public:
	void AddItem(class UItemBase* NewItemBase);

	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnGearChanged;

public:
	const TArray<class UItemBase*>& GetInven();
	UItemBase* const GetInvenItem(int32 InvenIndex);
	UItemBase* const GetGearItem(EGearType GearType);

public:
	void ClearInvenItem(int32 InvenIndex);

	void EquipGear(EGearType GearType , UItemBase* GearItem);
	void UnEquipGear(EGearType GearType);


};


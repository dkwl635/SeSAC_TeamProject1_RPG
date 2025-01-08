// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KJW/ItemData/ItemDataTable.h"
#include "InventoryComponent.generated.h"


//
class UItemBase;
class UStatsActorComponent;

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
	TArray<UItemBase*> Inven;

	UPROPERTY(VisibleAnywhere, Instanced)
	TMap<EGearType, UItemBase*> PlayerEqGears;

public:
	void AddItem(UItemBase* NewItemBase);
	void AddItem(UItemBase* NewItemBase, int32 InvenIndex);
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnGearChanged;

public:
	TArray<UItemBase*>& GetInven();
	UItemBase* GetInvenItem(int32 InvenIndex);
	UItemBase* GetGearItem(EGearType GearType);

public:
	void ClearInvenItem(int32 InvenIndex);
	void EquipGear(EGearType GearType , UItemBase* GearItem);
	void UnEquipGear(EGearType GearType);
	void SetGearStats(UItemBase* GearItem , bool bAddstats);
private:
	UPROPERTY()
	UStatsActorComponent* StatsComponent;

public :
	UFUNCTION(BlueprintCallable)
	void SetStatsComponent(UStatsActorComponent* NewStatsComponent);


};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJW/ItemData/ItemDataTable.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FItemData ItemData;

	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = "Item")
	int32 CurrentQuantity;

public:
	void InitializeItem(const FItemData& Data, int32 InitQuantity = 1)
	{
		ItemData = Data;
		CurrentQuantity = InitQuantity;
	}

public:
	UFUNCTION(BlueprintCallable)
	virtual FText GetItemName() const { return ItemData.ItemName; }
	UFUNCTION(BlueprintCallable)
	virtual FText GetItemDesc() const { return ItemData.ItemDesc; }
	UFUNCTION(BlueprintCallable)
	virtual EItemType GetItemType() const { return ItemData.ItemType; }
	UFUNCTION(BlueprintCallable)
	virtual EItemGrade GetItemGrade() const { return ItemData.ItemGrade; }

	UFUNCTION(BlueprintCallable)
	virtual UTexture2D* GetItemIcon() const { return ItemData.ItemIcon; }

};

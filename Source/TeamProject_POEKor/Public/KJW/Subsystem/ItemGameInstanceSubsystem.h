// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "KJW/ItemData/ItemDataTable.h"
#include "KJW/ItemData/ItemHeader.h"
#include "ItemGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,Abstract)
class TEAMPROJECT_POEKOR_API UItemGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class UDataTable* ItemDataTable = nullptr;


public: 
	UFUNCTION(BlueprintCallable)
	UItemBase* GetNewItem(int32 UniqueID , int32 CurrentQuantity = 1);

	bool GetItemData(FItemData& RefItemData, int32 UniqueID);
	FName GetItemTableRowName(int32 UniqueID);
private:

	TMap<int32, FName> ItemTableFindRowName;

};

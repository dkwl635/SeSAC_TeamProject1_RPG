// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataTable.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
    NONE = 0 UMETA(DisplayName = "NONE"),
    Gear = 1 UMETA(DisplayName = "Gear"),
    Potion = 2 UMETA(DisplayName = "Potion"),
    ETC = 3 UMETA(DisplayName = "ETC"),

};

UENUM(BlueprintType)
enum class EGearType : uint8
{
    NONE = 0 UMETA(DisplayName = "NONE"),
    Weapon = 1 UMETA(DisplayName = "Weapon"),
    Hat = 2 UMETA(DisplayName = "Hat"),
    Armor = 3 UMETA(DisplayName = "Armor"),
};


UENUM(BlueprintType)
enum class EItemGrade : uint8
{
    NONE = 0 UMETA(DisplayName = "NONE"),
    Common = 1 UMETA(DisplayName = "Common"),
    Uncommon = 2 UMETA(DisplayName = "Uncommon"),
    Rare = 3 UMETA(DisplayName = "Rare"),
    Legendary = 4 UMETA(DisplayName = "Legendary"),
};

USTRUCT(BlueprintType)
struct  TEAMPROJECT_POEKOR_API FItemData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    int32 UniqueID = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType = EItemType::NONE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemGrade ItemGrade = EItemGrade::NONE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxQuantity = 0;
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* ItemIcon = nullptr;
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ItemName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ItemDesc;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* ItemMesh ;

public:
    UPROPERTY(EditAnywhere , BlueprintReadWrite)
    FDataTableRowHandle StatusData;

public:
   void Copy(const FItemData& OtherItem);

};


USTRUCT(BlueprintType)
struct FGearStatus : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGearType GearType = EGearType::NONE;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AddState = 0;
public:
    void Copy(const FGearStatus& OtherItem);
};

/**
 * 
 */
UCLASS(BlueprintType)
class TEAMPROJECT_POEKOR_API UItemDataTable : public UDataTable
{
	GENERATED_BODY()
	
public:
      


};

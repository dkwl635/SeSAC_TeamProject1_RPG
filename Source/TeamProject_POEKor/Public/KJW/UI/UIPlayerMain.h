// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJW/UI/UIBase.h"
#include "UIPlayerMain.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EUIType : uint8
{
    NONE = 0 UMETA(DisplayName = "NONE"),
    Inven = 1 UMETA(DisplayName = "Inven"),
};


USTRUCT(BlueprintType)
struct  TEAMPROJECT_POEKOR_API FUIGroup 
{
    GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUIType UIType = EUIType::NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUIBase> UIClass;


};


UCLASS()
class TEAMPROJECT_POEKOR_API UUIPlayerMain : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FUIGroup> InitUIGroup;
	
	UPROPERTY()
	TMap<EUIType, UUIBase*> UIMap;
public:

	virtual void NativeConstruct() override;
};

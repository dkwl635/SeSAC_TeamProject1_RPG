// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UISlotBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EUISlotType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	Inven = 1 UMETA(DisplayName = "Inven"),
};


UCLASS()
class TEAMPROJECT_POEKOR_API UUISlotBase : public UUserWidget
{
	GENERATED_BODY()
	

protected: 
	UPROPERTY(VisibleAnywhere)
	EUISlotType SlotType = EUISlotType::NONE;

};

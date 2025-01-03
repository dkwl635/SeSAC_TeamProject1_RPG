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
	Gear = 2 UMETA(DisplayName = "Gear"),
};


UCLASS()
class TEAMPROJECT_POEKOR_API UUISlotBase : public UUserWidget
{
	GENERATED_BODY()
	

public:
	static bool IsOnClickedSlot;
	static UUISlotBase* ClickedSlot;


protected: 
	UPROPERTY(VisibleAnywhere)
	EUISlotType SlotType = EUISlotType::NONE;
	UPROPERTY(VisibleAnywhere)
	UUserWidget* ParentUserWidget = nullptr;
public:
	UFUNCTION(BlueprintCallable)
	virtual	bool IsMoveSlot();
	UFUNCTION(BlueprintCallable)
	virtual	bool IsShowParent();
	UFUNCTION(BlueprintCallable)
	void SetParent(UUserWidget* NewParent);


public:
	UFUNCTION(BlueprintCallable)
	void OnClickedSlot();


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJW/UI/UIBase.h"
#include "UIInventory.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UUIInventory : public UUIBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* SlotUniformGridPanel;
	
protected:
	UPROPERTY()
	TArray<class UInvenSlot*> InvenSlots;
	
	UPROPERTY()
	class UInventoryComponent* PlayerInven;

protected:
	virtual void InitUI() override;

public:
	virtual void ShowUI() override;
	virtual void HideUI() override;

private:
	UFUNCTION()
	void SetInvenSlots();

};

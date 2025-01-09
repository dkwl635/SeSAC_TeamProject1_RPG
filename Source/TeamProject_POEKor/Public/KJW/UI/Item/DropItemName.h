// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropItemName.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UDropItemName : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,meta = (Bindwidget))
	class UTextBlock* TextBlock_ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bindwidget))
	class UButton* Button_Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ADropItem* DropItem;
public:
	virtual void NativeConstruct();

	UFUNCTION()
	void DropItemButtonAction();

	UFUNCTION(BlueprintCallable)
	void SetDropItem(ADropItem* NewDropItem);

};

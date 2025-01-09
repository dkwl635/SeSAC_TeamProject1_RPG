// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoBox.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UItemInfoBox : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere , BlueprintReadWrite , meta = (BindWidget))
	UImage* Image_Item;
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite , meta = (BindWidget))
	UTextBlock* TextBlock_ItemName;
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite , meta = (BindWidget))
	UTextBlock* TextBlock_ItemDesc;

public :

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetItemInfoBox(class UItemBase* Item);
	UFUNCTION(BlueprintCallable)
	void HideInfoBox();
};

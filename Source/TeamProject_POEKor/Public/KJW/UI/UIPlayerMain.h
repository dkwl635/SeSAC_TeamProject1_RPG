// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJW/UI/UIBase.h"
#include "UIPlayerMain.generated.h"

/**
 * 
 */



UCLASS()
class TEAMPROJECT_POEKOR_API UUIPlayerMain : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	int32 PlayerUIZOredr = 10;

	UPROPERTY(EditAnywhere , meta = (BindWidget))
	class UUIBottom* WBP_Bottom;
public:
	UPROPERTY()
	TMap<EUIType, UUIBase*> UIMap;
	UPROPERTY()
	TArray<UUIBase*> UIList;

public:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void ShowUI(EUIType UIType);
	UFUNCTION(BlueprintCallable)
	void HideUI(EUIType UIType);

	UFUNCTION(BlueprintCallable)
	void ToggleUI(EUIType UIType);

private:
	void UpdateZOrder();
};

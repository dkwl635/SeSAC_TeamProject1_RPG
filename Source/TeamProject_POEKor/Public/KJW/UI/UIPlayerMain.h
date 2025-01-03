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
	

public:
	UPROPERTY()
	TMap<EUIType, UUIBase*> UIMap;
public:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	void ShowUI(EUIType UIType);

	UFUNCTION(BlueprintCallable)
	void ToggleUI(EUIType UIType);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UUIBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool bIsInit = false;
	virtual void InitUI();
public:
	
	virtual void ShowUI();
	virtual void RefreshUI();
	virtual void HideUI();
	virtual void TopUI();

	//return UI Show(true)/Hide(false)
	virtual bool ToggleUI();
};

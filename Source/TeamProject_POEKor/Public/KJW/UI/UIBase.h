// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EUIType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	Inven = 1 UMETA(DisplayName = "Inven"),
	PlayerInfo = 2 UMETA(DisplayName = "PlayerInfo"),
	EUIMax = 10 UMETA(DisplayName = "EUIMax")
};


UCLASS()
class TEAMPROJECT_POEKOR_API UUIBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool bIsInit = false;
public:

	virtual void InitUI();
protected:
	UPROPERTY(VisibleAnywhere)
	EUIType UIType = EUIType::NONE;

	class UCanvasPanelSlot* CanvasSlot = nullptr;
public:
	EUIType GetUIType() { return UIType; }
	class UCanvasPanelSlot* GetCanvasSlot();
public:
	
	virtual void ShowUI();
	virtual void RefreshUI();
	virtual void HideUI();
	virtual void TopUI();

	//return UI Show(true)/Hide(false)
	virtual bool ToggleUI();

	virtual void SetZOrder(int32 NewZOrder);

};

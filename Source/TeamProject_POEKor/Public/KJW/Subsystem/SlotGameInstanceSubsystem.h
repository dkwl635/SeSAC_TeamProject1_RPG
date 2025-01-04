// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "KJW/OtherUI/Slot/UISlotHeader.h"
#include "SlotGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API USlotGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	


protected:
	TWeakObjectPtr<class UUIPlayerMain> UIPlayerMain;
public:
	bool IsOnClickedSlot;
	TWeakObjectPtr<UUISlotBase> ClickedSlot;
	TWeakObjectPtr<UWorld> SlotWorld;


	UFUNCTION(BlueprintCallable)
	void OnClikedSlot(UUISlotBase* NewClickedSlot);
	UFUNCTION(BlueprintCallable)
	void FailedMoveSlot();

	UFUNCTION(BlueprintCallable)
	void SetMainUserWidget(class UUIPlayerMain* NewUIPlayerMain);

protected:
	void ClearClickSlot();
	void SetNewClickSlot(UUISlotBase* NewClickedSlot);
	
	void MoveSlotEvent(UUISlotBase* FromSlot, UUISlotBase* ToSlot);


};

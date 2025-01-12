// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SlotGameInstanceSubsystem.generated.h"

/**
 * 
 */
class UUISlotBase;

UCLASS()
class TEAMPROJECT_POEKOR_API USlotGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	


public:
	bool IsOnClickedSlot;
	TWeakObjectPtr<UUISlotBase> ClickedSlot;
	TWeakObjectPtr<UWorld> SlotWorld;


	UFUNCTION(BlueprintCallable)
	void OnClikedSlot(UUISlotBase* NewClickedSlot);
	UFUNCTION(BlueprintCallable)
	void FailedMoveSlot();


protected:
	void ClearClickSlot();
	void SetNewClickSlot(UUISlotBase* NewClickedSlot);
	
	void MoveSlotEvent(UUISlotBase* FromSlot, UUISlotBase* ToSlot);


};

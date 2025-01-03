// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/Game/POEGameInstance.h"
#include "KJW/OtherUI/Slot/UISlotBase.h"
void UPOEGameInstance::Shutdown()
{
	UUISlotBase::IsOnClickedSlot = false;
	UUISlotBase::ClickedSlot = nullptr;

}

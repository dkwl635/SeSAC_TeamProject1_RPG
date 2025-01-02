// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "POEGameInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class TEAMPROJECT_POEKOR_API UPOEGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UItemGameInstanceSubsystem> temGameInstanceSubsystemClass;

};

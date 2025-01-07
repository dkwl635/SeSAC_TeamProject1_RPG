// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindTarget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_POEKOR_API UFindTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetKeyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AttackDistanceKeyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetDistanceKeyName;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/BTTaskNode/EnemyAttack.h"
#include "KJW/Enemy.h"
#include "AIController.h"

EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn)
	{
		AEnemy* Enemy = Cast<AEnemy>(OwnerPawn);
		if (Enemy)
		{
			Enemy->AttackStart();
		}

	}

	return EBTNodeResult::Type::Succeeded;
}

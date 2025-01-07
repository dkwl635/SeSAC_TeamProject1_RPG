// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/BTTaskNode/FindTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "KJW/Enemy.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UFindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKeyName);
	ACharacter* Target = Cast<ACharacter>(TargetObject);
	AAIController* AIController = OwnerComp.GetAIOwner();
	

	float TargetDistance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TargetDistanceKeyName);
	float AttackDistance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AttackDistanceKeyName);

	FVector ActorLocation = AIController->GetPawn()->GetActorLocation();
	
	if (Target)
	{
		 //FVector TargetLocation = Target->GetActorLocation();
		 //FVector::Distance(ActorLocation, TargetLocation);
		 float Distance = AIController->GetPawn()->GetDistanceTo(Target);
		 
		 if (Distance <= AttackDistance)
		 {
			 return EBTNodeResult::Failed;
			
		 }
		 else
		 {
			 return EBTNodeResult::Succeeded;
		 }



	}
	else
	{
		ACharacter* NewTarget = UGameplayStatics::GetPlayerCharacter(OwnerComp.GetWorld(), 0);
		if (NewTarget)
		{
			float Distance = AIController->GetPawn()->GetDistanceTo(NewTarget);
			//UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
			if (Distance < TargetDistance)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKeyName, NewTarget);

				AEnemy* Enemy = Cast<AEnemy>(AIController->GetPawn());
				if (Enemy)
				{
					Enemy->SetTarget(NewTarget);
				}

				return EBTNodeResult::Succeeded;
			}
			else
			{
				return EBTNodeResult::Failed;
			}
		}
		else
		{
			return EBTNodeResult::Failed;
		}

		
	}

	
}
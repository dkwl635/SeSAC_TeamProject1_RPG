// Fill out your copyright notice in the Description page of Project Settings
#include "KJW/Actor/Boss/Boss.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABoss::ABoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BodyCollisiopn"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	SetRootComponent(BodyCollision);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());



}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* NewTarget =	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (NewTarget)
	{
		SetTarget(NewTarget);
	}

	UAnimInstance* BossAnimInstane = SkeletalMeshComponent->GetAnimInstance();
	if (BossAnimInstane)
	{
		BossAnimInstane->OnMontageEnded.AddDynamic(this, &ThisClass::EndAnimMontage);

	}
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WorldDeltaTime = DeltaTime;
	if (!TargetCharacter) { return; }

	TickBoss();

}

// Called to bind functionality to input
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ABoss::TickBoss()
{
	TickState();
	TickCool();
	RotUpdate();
	TickPattern();
}


void ABoss::RotUpdate()
{
	if (!TargetCharacter) { return; }

	if (bRotTarget)
	{
		bool bShortestPath = true;

		FVector BossLocation = GetActorLocation();
		BossLocation.Z = 0;

		FVector TargetLocation = TargetCharacter->GetActorLocation();
		TargetLocation.Z = 0;

		FRotator StartRot = GetActorRotation();
		FRotator EndRot = UKismetMathLibrary::FindLookAtRotation(BossLocation, TargetLocation);

		FRotator NextRot = UKismetMathLibrary::RLerp(StartRot, EndRot, RotDelta, bShortestPath);
		SetActorRotation(NextRot);
	}
}

void ABoss::TickState()
{
	if (!TargetCharacter) { return; }

	TargetDistance = GetDistanceTo(TargetCharacter);

	EBossState NewBossState = BossState;
	if (TargetDistance <= NormalAttackDistance && (BossState == EBossState::TrakingTarget || BossState == EBossState::Idle))
	{
		NewBossState = EBossState::Idle;
		if (NormalAttackCoolTimer <= 0)
		{
			NewBossState = EBossState::NormalAttack;
		}
	}

	if (BossState == EBossState::Idle && IdleCoolTimer < 0)
	{
		NewBossState = EBossState::TrakingTarget;
	}

	SetNewState(NewBossState);


	if (BossState == EBossState::TrakingTarget)
	{
		TrakingTarget();
	}
}

void ABoss::TickCool()
{
	if (NormalAttackCoolTimer > 0 && BossState == EBossState::Idle) { NormalAttackCoolTimer -= WorldDeltaTime; }

	if (IdleCoolTimer > 0 && BossState == EBossState::Idle) { IdleCoolTimer -= WorldDeltaTime; }
}

void ABoss::SetTarget(ACharacter* NewTarget)
{
	if (NewTarget)
	{
		TargetCharacter = NewTarget;
		SetNewState(EBossState::TrakingTarget);
	}
}

void ABoss::SetNewState(EBossState NewBossState)
{
	if (BossState == NewBossState)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("%d") ,(int32)NewBossState);

	if (NewBossState == EBossState::NormalAttack)
	{	
		bool IsSuccess = AttackStart(EBossState::NormalAttack);
		if (IsSuccess)
		{
			NewBossState = EBossState::NormalAttack;
		}
		else 
		{
			NewBossState = EBossState::Idle;
		}
		
	
	}
	else if (NewBossState == EBossState::Idle)
	{
		IdleCoolTimer = IdleCoolTime;
		bRotTarget = true;
	}
	else if (NewBossState == EBossState::TrakingTarget)
	{
		bRotTarget = true;
	}

	BossState = NewBossState;
}

bool ABoss::AttackStart(EBossState AttackBossState)
{
	if (AttackAnimMontage.Contains(AttackBossState))
	{
		if (SkeletalMeshComponent->GetAnimInstance())
		{
			ClearAttackEvent();
			UE_LOG(LogTemp, Warning, TEXT("%s End"), *AttackAnimMontage[AttackBossState]->GetName());
			SkeletalMeshComponent->GetAnimInstance()->Montage_Play(AttackAnimMontage[AttackBossState]);
			return true;
		}
	}

	return false;
}

void ABoss::AttackTarget(ACharacter* Charactertarget)
{
	if (!IsAttackEvent)
	{
		IsAttackEvent = true;
		AttackEvent(Charactertarget);
	}
	else
	{
		return;
	}
}



float ABoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (Hp <= 0)
	{
		return 0;
	}

	Hp -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Boss : %f"), Hp);
	UE_LOG(LogTemp, Warning, TEXT("Damge : %f"), Damage);
	if (Hp <= 0)
	{
		DieStart();
	}

	return 0.f;
}

void ABoss::TrakingTarget()
{
	FVector CurrentPos = GetActorLocation();
	FVector EndPos = (WorldDeltaTime * TrakingSpeed) * GetActorForwardVector() + CurrentPos;

	SetActorLocation(EndPos);
}

void ABoss::ClearAttackEvent()
{
	IsAttackEvent = false;
}

void ABoss::EndAnimMontage(UAnimMontage* AnimMontage , bool IsEnded)
{
	UE_LOG(LogTemp, Warning, TEXT("%s End"), *AnimMontage->GetName());
	SetNewState(EBossState::Idle);
}

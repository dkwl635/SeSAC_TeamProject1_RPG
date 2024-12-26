// Fill out your copyright notice in the Description page of Project Settings
#include "KJW/Actor/Boss/Boss.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BodyCollisiopn"));
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
	//CheckTarget -> TargetDistance
	CheckDistance();
	TickCool();
	RotUpdate();
	TickState();
}
void ABoss::CheckDistance()
{
	if (!TargetCharacter) { return; }

	TargetDistance = GetDistanceTo(TargetCharacter);

	if (TargetDistance <= NormalAttackDistance && (BossState == EBossState::TrakingTarget || BossState == EBossState::Idle))
	{
		SetNewState(EBossState::NormalAttack);
	}
	
}

void ABoss::RotUpdate()
{
	if (!TargetCharacter) { return; }

	if (BossState == EBossState::TrakingTarget)
	{
		float Delta = 0.8f;
		bool bShortestPath = true;

		FVector BossLocation = GetActorLocation();
		BossLocation.Z = 0;

		FVector TargetLocation = TargetCharacter->GetActorLocation();
		TargetLocation.Z = 0;

		FRotator StartRot = GetActorRotation();
		FRotator EndRot = UKismetMathLibrary::FindLookAtRotation(BossLocation, TargetLocation);

		FRotator NextRot = UKismetMathLibrary::RLerp(StartRot, EndRot, Delta, bShortestPath);
		SetActorRotation(NextRot);
	}
}

void ABoss::TickState()
{
	if (BossState == EBossState::TrakingTarget)
	{
		TrakingTarget();
	}

	if (BossState == EBossState::Idle && IdleCoolTimer < 0)
	{
		IdleCoolTimer = IdleCoolTime;
		SetNewState(EBossState::TrakingTarget);
	}
}

void ABoss::TickCool()
{
	if (NormalAttackCoolTimer > 0) { NormalAttackCoolTimer -= WorldDeltaTime; }

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

	

	if (NewBossState == EBossState::NormalAttack)
	{	
		if (NormalAttackCoolTimer <= 0)
		{
			AttackStart();
			NormalAttackCoolTimer = NormalAttackCoolTime;
		}
		else
		{
			NewBossState = EBossState::Idle;
		}
	}
	else if (NewBossState == EBossState::Idle)
	{
		
	}

	BossState = NewBossState;
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

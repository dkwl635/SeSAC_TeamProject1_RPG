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
	OrginRotSpeed = RotSpeed;
	BossState = EBossState::Idle;
	
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
	if (BossState == EBossState::Death) { return; }

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

		FRotator NextRot = UKismetMathLibrary::RLerp(StartRot, EndRot, RotSpeed, bShortestPath);
		SetActorRotation(NextRot);
	}
}

void ABoss::TickState()
{
	if (!TargetCharacter) { return; }
	

	TargetDistance = GetDistanceTo(TargetCharacter);

	EBossState NewBossState = BossState;

	if (BossState != EBossState::NormalAttack && BossState != EBossState::Pattern1)
	{
		if (TargetDistance <= NormalAttackDistance)
		{
			NewBossState = EBossState::Idle;		
		}	


		if (IsStartPattern1())
		{
			NewBossState = EBossState::Pattern1;
		}
		else if (TargetDistance <= NormalAttackDistance && NormalAttackCoolTimer <= 0.f)
		{
			NewBossState = EBossState::NormalAttack;
		}
	}

	SetNewState(NewBossState);
	

	if (BossState == EBossState::Idle && NewBossState == EBossState::Idle && IdleCoolTimer < 0)
	{
		NewBossState = EBossState::TrakingTarget;
		SetNewState(NewBossState);
	}
	
	if (BossState == EBossState::TrakingTarget)
	{
		TrakingTarget();
	}
}

void ABoss::TickCool()
{


	if (NormalAttackCoolTimer > 0 && BossState == EBossState::Idle) { NormalAttackCoolTimer -= WorldDeltaTime; }
	if (IdleCoolTimer > 0 && BossState == EBossState::Idle) { IdleCoolTimer -= WorldDeltaTime; }
	if (Pattern1CoolTimer > 0 && BossState != EBossState::Pattern1) { Pattern1CoolTimer -= WorldDeltaTime; }
}

void ABoss::SetTarget(ACharacter* NewTarget)
{
	if (NewTarget)
	{
		TargetCharacter = NewTarget;
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
		NewBossState = EBossState::NormalAttack;
		if (IsSuccess) { NormalAttackCoolTimer = NormalAttackCoolTime; }
		else { NewBossState = EBossState::Idle; }
	}
	else if (NewBossState == EBossState::Pattern1)
	{
		bool IsSuccess = AttackStart(EBossState::Pattern1);
		Pattern1CoolTimer = Pattern1CoolTime;
		if (IsSuccess) { NewBossState = EBossState::Pattern1; }
		else { NewBossState = EBossState::Idle; }
	}
	else if (NewBossState == EBossState::Idle)
	{
		RotSpeed = OrginRotSpeed;
		IdleCoolTimer = IdleCoolTime;
		bRotTarget = true;
	}
	else if (NewBossState == EBossState::TrakingTarget)
	{
		RotSpeed = OrginRotSpeed;
		bRotTarget = true;
	}
	else if (NewBossState == EBossState::Death)
	{
		DieStart();
	}

	BossState = NewBossState;
}

bool ABoss::AttackStart(EBossState AttackBossState)
{
	ClearAttackEvent();
	return StartBossAnim(AttackBossState);
}

bool ABoss::StartBossAnim(EBossState StartBossState)
{
	if (SkeletalMeshComponent->GetAnimInstance())
	{
		if (AttackAnimMontage.Contains(StartBossState))
		{
		PlayMontageLength = SkeletalMeshComponent->GetAnimInstance()->Montage_Play(AttackAnimMontage[StartBossState]);
		return true;
		}

	}
	return false;
}

void ABoss::DieStart()
{
	if (StartBossAnim(EBossState::Death))
	{
		StartDeathEffect();
	}
}

void ABoss::DieEnd()
{
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
	
	if (BossState == EBossState::Death) { return 0; }
	
	if (Hp <= 0)
	{
		return 0;
	}

	Hp -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Boss : %f"), Hp);
	UE_LOG(LogTemp, Warning, TEXT("Damge : %f"), Damage);
	if (Hp <= 0)
	{
		SetNewState(EBossState::Death);
		//DieStart();
	}

	return 0.f;
}

void ABoss::TrakingTarget()
{
	FVector CurrentPos = GetActorLocation();
	FVector EndPos = (WorldDeltaTime * TrakingSpeed) * GetActorForwardVector() + CurrentPos;

	SetActorLocation(EndPos , true);
}

void ABoss::ClearAttackEvent()
{
	IsAttackEvent = false;
}

void ABoss::SetRotSpeed(float NewSpeed)
{
	if (NewSpeed > 1)
	{
		NewSpeed = 1;
	}
	else if (NewSpeed <= 0)
	{
		NewSpeed = 0;
	}

	RotSpeed = NewSpeed;
}


void ABoss::EndAnimMontage(UAnimMontage* AnimMontage , bool IsEnded)
{
	if (BossState == EBossState::Death)
	{
		return;
	}

	if (IsEnded == true)
	{
		SetNewState(EBossState::Idle);
		return;
	}
	else if (IsEnded == false)
	{
		SetNewState(EBossState::Idle);
		return;
	}

	
}


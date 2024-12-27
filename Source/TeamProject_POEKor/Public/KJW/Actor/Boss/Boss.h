// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Boss.generated.h"

UENUM(BlueprintType)
enum class EBossState : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	Idle UMETA(DisplayName = "Idle"),
	NormalAttack UMETA(DisplayName = "NormalAttack"),
	TrakingTarget UMETA(DisplayName = "TrakingTarget"),
	Pattern1 UMETA(DisplayName = "Parttern1"),
	
};

UCLASS()
class TEAMPROJECT_POEKOR_API ABoss : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* BodyCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMeshComponent;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBossState BossState = EBossState::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage")
	TMap<EBossState, UAnimMontage*> AttackAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHp = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hp = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AtkPower = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TrakingSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRotTarget = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotDelta = 0.02f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAttackEvent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "NormalAttack")
	float NormalAttackDistance = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NormalAttack")
	float NormalAttackCoolTime = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NormalAttack")
	float NormalAttackCoolTimer = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float IdleCoolTime = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float IdleCoolTimer = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacter* TargetCharacter;

	float WorldDeltaTime = 0.f;
public: 

	void TickBoss();
	
public:

	//Boss Rot
	void RotUpdate();
	void TickState();
	void TickCool();
	UFUNCTION(BlueprintImplementableEvent)
	void TickPattern();
	UFUNCTION(BlueprintCallable)
	void SetTarget(class ACharacter* NewTarget);
	
	UFUNCTION(BlueprintCallable)
	void SetNewState(EBossState NewBossState);

public:
	UFUNCTION(BlueprintCallable)
	bool AttackStart(EBossState AttackBossState);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DieStart();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DieEnd();

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:

	void TrakingTarget();
	UFUNCTION(BlueprintCallable)
	void ClearAttackEvent();
	UFUNCTION(BlueprintCallable)
	void AttackTarget(ACharacter* Charactertarget);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AttackEvent(ACharacter* Charactertarget);
	UFUNCTION()
	void EndAnimMontage(UAnimMontage* AnimMontage, bool IsEnded);
};

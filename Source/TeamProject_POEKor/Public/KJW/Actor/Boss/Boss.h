// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Boss.generated.h"

UENUM(BlueprintType)
enum class EBossState : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	Death UMETA(DisplayName = "Death"),
	Idle UMETA(DisplayName = "Idle"),
	NormalAttack UMETA(DisplayName = "NormalAttack"),
	TrakingTarget UMETA(DisplayName = "TrakingTarget"),
	Pattern1 UMETA(DisplayName = "Pattern1"),
	Pattern2 UMETA(DisplayName = "Pattern2"),
	Stun UMETA(DisplayName = "Stun"),
	
};

DECLARE_MULTICAST_DELEGATE(FUpdateStatsValue);

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BossName = "Boss";

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBossState BossState = EBossState::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage")
	TMap<EBossState, UAnimMontage*> AttackAnimMontage;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHp = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hp = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AtkPower = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunCount = 10; 

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TrakingSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotSpeed = 0.02f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsAttackEvent = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlayMontageLength = 0.f;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRotTarget = true;
protected:
	UPROPERTY(EditAnywhere, Category = "Idle")
	float IdleCoolTime = 0.5f;
	UPROPERTY(EditAnywhere, Category = "Idle")
	float IdleCoolTimer = 0.5f;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern1")
	float Pattern1Distance = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern1")
	float Pattern1CoolTimer = 1.f;
	UPROPERTY(EditAnywhere, Category = "Pattern1")
	float Pattern1CoolTime = 5.f;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern2")
	float Pattern2Distance = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pattern2")
	float Pattern2CoolTimer = 1.f;
	UPROPERTY(EditAnywhere, Category = "Pattern2")
	float Pattern2CoolTime = 5.f;
protected:
	UPROPERTY(EditAnywhere, Category = "NormalAttack")
	float NormalAttackDistance = 300.f;
	UPROPERTY(EditAnywhere, Category = "NormalAttack")
	float NormalAttackCoolTime = 1.f;
	UPROPERTY(EditAnywhere, Category = "NormalAttack")
	float NormalAttackCoolTimer = 1.f;
protected:
	UPROPERTY(BlueprintReadOnly)
	float TargetDistance = 100.f;
private:
	float WorldDeltaTime = 0.f;
	float OrginRotSpeed = 0.f;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacter* TargetCharacter;
	bool bStunPossible = false;
public:
	//Tick Boss Function
	void TickBoss();

public:
	//Rotate towards target
	void RotUpdate();
	//On the state Tick
	void TickState();
	//Cool Time tick
	void TickCool();

	UFUNCTION(BlueprintImplementableEvent)
	void TickPattern();
	UFUNCTION(BlueprintCallable)
	void SetTarget(class ACharacter* NewTarget);
	UFUNCTION(BlueprintCallable)
	void SetNewState(EBossState NewBossState);
	//Anim Event Check
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AnimNotifyEvent();
public:
	//Check Attackable
	UFUNCTION(BlueprintCallable)
	bool AttackStart(EBossState AttackBossState);
	//StartAnimMontage Function
	UFUNCTION(BlueprintCallable)
	bool StartBossAnim(EBossState StartBossState);

	//Start Die Event
	UFUNCTION(BlueprintCallable)
	void DieStart();

	//StartDeathEffect
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartDeathEffect();

	//End Die Event
	UFUNCTION(BlueprintCallable)
	void DieEnd();

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
private:
	void TrakingTarget();

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetAttackCollision(bool OnOff);

	UFUNCTION(BlueprintCallable)
	void ClearAttackEvent();
	UFUNCTION(BlueprintCallable)
	void AttackTarget(ACharacter* Charactertarget);
	UFUNCTION(BlueprintCallable)
	void SetRotSpeed(float NewSpeed);
protected:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AttackEvent(ACharacter* Charactertarget);
	UFUNCTION()
	void EndAnimMontage(UAnimMontage* AnimMontage, bool IsEnded);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool IsStartPattern1();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool IsStartPattern2();
public:

	FUpdateStatsValue UpdateHp;
	FUpdateStatsValue UpdateStun;



};

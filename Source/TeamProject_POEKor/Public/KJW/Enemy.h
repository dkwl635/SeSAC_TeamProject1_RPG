// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class TEAMPROJECT_POEKOR_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere)
	class USphereComponent* BodyCollision;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* FloatingPawnMovement;

public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float MaxHp = 10;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float Hp = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacter* TargetCharacter;

public:

	//Check Enemy Die
	UFUNCTION(BlueprintCallable)
	bool IsDie();

	//Monster Rot
	void RotUpdate();


};

// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "GameFramework/Character.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BodyCollisiopn"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	SetRootComponent(BodyCollision);

	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotUpdate();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemy::IsDie()
{
	
	return Hp <= 0;
}

void AEnemy::RotUpdate()
{
	FRotator NextRot;
	
	FRotator StartRot = GetActorRotation();
	FRotator EndRot = FRotator::ZeroRotator;
	float Delta = 0.9;
	bool bShortestPath = true;
	

	
	if (TargetCharacter)
	{
		FVector ActorLocation = GetActorLocation();
		FVector TargetLocation = TargetCharacter->GetActorLocation();
		EndRot =	UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLocation);
		EndRot.Pitch = 0;
	}
	else
	{
		if (GetController())
		{
			EndRot = GetControlRotation();
		}	
	}

	NextRot = UKismetMathLibrary::RLerp(StartRot, EndRot, Delta, bShortestPath);
	SetActorRotation(NextRot);

}

void AEnemy::SetTarget(ACharacter* NewTarget)
{
	TargetCharacter = NewTarget;
}

float AEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (Hp <= 0)
	{
		return 0;
	}

	Hp -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Enemy : %f") , Hp);
	UE_LOG(LogTemp, Warning, TEXT("Damge : %f") , Damage);
	if (Hp <= 0)
	{
		DieStart();
	}

	return 0.f;
}


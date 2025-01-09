// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropItem.generated.h"

UCLASS()
class TEAMPROJECT_POEKOR_API ADropItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Instanced)
	class UItemBase* Item = nullptr;

public :
	UFUNCTION(BlueprintCallable)
	void AddItem();
protected:
	UFUNCTION(BlueprintCallable)
	void OnCharacterOverlap(AActor* OtherActor);
	

};

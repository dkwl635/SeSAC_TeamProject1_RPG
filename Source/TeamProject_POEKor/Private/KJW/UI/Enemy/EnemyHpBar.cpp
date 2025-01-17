// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/UI/Enemy/EnemyHpBar.h"

#include "Components/ProgressBar.h"


void UEnemyHpBar::SetHpBarPercent(float percent)
{
	if (percent <= 0.0f || percent >= 1.0f)
	{
		Hpbar->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else
	{
		Hpbar->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	CurrentHpPercent = percent;
	
	if (FMath::IsNearlyEqual(TempHpPercent, CurrentHpPercent, 0.01f)) { return; }

	if (HpTimeHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(HpTimeHandle);
	}
	
	GetWorld()->GetTimerManager().SetTimer(HpTimeHandle, this, &ThisClass::HpBarLerp, GetWorld()->GetDeltaSeconds(), true);
}

void UEnemyHpBar::HpBarLerp()
{
	
	TempHpPercent = FMath::FInterpTo(TempHpPercent, CurrentHpPercent, GetWorld()->GetDeltaSeconds(), 10.f);
	
	UE_LOG(LogTemp, Warning, TEXT("%f"), TempHpPercent);
	Hpbar->SetPercent(TempHpPercent);

	if (FMath::IsNearlyEqual(TempHpPercent, CurrentHpPercent, 0.01f))
	{
		TempHpPercent = CurrentHpPercent;
		Hpbar->SetPercent(TempHpPercent);
		GetWorld()->GetTimerManager().ClearTimer(HpTimeHandle);
	}

}

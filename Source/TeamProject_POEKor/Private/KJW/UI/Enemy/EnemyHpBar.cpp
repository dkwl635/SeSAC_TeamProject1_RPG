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
	
	GetWorld()->GetTimerManager().SetTimer(HpTimeHandle, this, &ThisClass::HpBarLerp, 0.02f, true);
}

void UEnemyHpBar::HpBarLerp()
{
	

	if (FMath::IsNearlyEqual(TempHpPercent, CurrentHpPercent , 0.01f))
	{
		GetWorld()->GetTimerManager().ClearTimer(HpTimeHandle);
		
	}
	else if(TempHpPercent > CurrentHpPercent)
	{
		//TempHpPercent = FMath::FInterpTo(TempHpPercent, CurrentHpPercent, 0.02f, 10.f);
		TempHpPercent = FMath::Lerp(TempHpPercent, CurrentHpPercent ,0.2f);
	}
	else
	{
		//TempHpPercent = FMath::FInterpTo(CurrentHpPercent, TempHpPercent, 0.02f, 10.f);
		
		TempHpPercent=	FMath::Lerp(CurrentHpPercent, TempHpPercent, 0.2f);
	}

	UE_LOG(LogTemp, Warning, TEXT("%f"), TempHpPercent);
	Hpbar->SetPercent(TempHpPercent);

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/UI/Enemy/EnemyHpBar.h"

#include "Components/ProgressBar.h"


void UEnemyHpBar::SetHpBarPercent(float percent)
{
	if (percent <= 0.0f || percent >= 1.0f)
	{
		Hpbar->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Hpbar->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	Hpbar->SetPercent(percent);
}

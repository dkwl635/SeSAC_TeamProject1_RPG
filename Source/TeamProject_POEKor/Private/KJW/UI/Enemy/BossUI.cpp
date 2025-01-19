// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/UI/Enemy/BossUI.h"
#include "KJW/Actor/Boss/Boss.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBossUI::SetBoss(ABoss* NewBoss)
{
	boss = NewBoss;

	boss->BossName;

	boss->UpdateHp.AddUObject(this, &ThisClass::SetHpBar);
	boss->UpdateStun.AddUObject(this, &ThisClass::SetStunBar);

	SetHpBar();
	SetStunBar();
	ProgressBar_Stun->SetPercent(0.f);
}

void UBossUI::SetHpBar()
{
	float Hp = boss->Hp;
	float MaxHp = boss->MaxHp;

	TextBlock_Hp->SetText(FText::AsNumber(Hp));
	TextBlock_MaxHp->SetText(FText::AsNumber(MaxHp));

	float percent = Hp / MaxHp;
	CurrentHpPercent = percent;

	if (FMath::IsNearlyEqual(TempHpPercent, CurrentHpPercent, 0.01f))
	{
		TempHpPercent = CurrentHpPercent;
		ProgressBar_Hp->SetPercent(TempHpPercent);
		return;
	}

	if (!HpTimeHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(HpTimeHandle, this, &ThisClass::HpBarLerp, GetWorld()->GetDeltaSeconds(), true);
	}
	
}

void UBossUI::SetStunBar()
{

	float StunCount = boss->StunCount;
	float StunMax = 10.f;

	CurrentStunPercent = 1.f - StunCount / StunMax;
	if (!(FMath::IsNearlyEqual(TempStunPercent, CurrentStunPercent, 0.01f)))
	{
		if (!StunTimeHandle.IsValid())
			GetWorld()->GetTimerManager().SetTimer(StunTimeHandle, this, &ThisClass::StunBarLerp, GetWorld()->GetDeltaSeconds(), true);
	}
}

void UBossUI::HpBarLerp()
{
	TempHpPercent = FMath::FInterpTo(TempHpPercent, CurrentHpPercent, GetWorld()->GetDeltaSeconds(), 10.f);

	UE_LOG(LogTemp, Warning, TEXT("%f"), TempHpPercent);
	ProgressBar_Hp->SetPercent(TempHpPercent);

	if (FMath::IsNearlyEqual(TempHpPercent, CurrentHpPercent, 0.01f))
	{
		TempHpPercent = CurrentHpPercent;
		ProgressBar_Hp->SetPercent(TempHpPercent);
		GetWorld()->GetTimerManager().ClearTimer(HpTimeHandle);

		if (!FMath::IsNearlyEqual(TempHpShadowPercent, CurrentHpPercent, 0.01f))
		{
			if (!HpShadowTimeHandle.IsValid())
				GetWorld()->GetTimerManager().SetTimer(HpShadowTimeHandle, this, &ThisClass::HpBarShadowLerp, GetWorld()->GetDeltaSeconds(), true, 1.f);
		}
	}
}

void UBossUI::HpBarShadowLerp()
{
	TempHpShadowPercent = FMath::FInterpConstantTo(TempHpShadowPercent, TempHpPercent, GetWorld()->GetDeltaSeconds(), 0.5f);
	ProgressBar_HpShadow->SetPercent(TempHpShadowPercent);

	if (FMath::IsNearlyEqual(TempHpShadowPercent, TempHpPercent, 0.01f))
	{
		TempHpShadowPercent = TempHpPercent;
		ProgressBar_HpShadow->SetPercent(TempHpShadowPercent);
		GetWorld()->GetTimerManager().ClearTimer(HpShadowTimeHandle);
	}
}

void UBossUI::StunBarLerp()
{
	TempStunPercent = FMath::FInterpConstantTo(TempStunPercent, CurrentStunPercent, GetWorld()->GetDeltaSeconds(), 0.5f);
	ProgressBar_Stun	->SetPercent(TempStunPercent);

	if (FMath::IsNearlyEqual(TempStunPercent, CurrentStunPercent, 0.01f))
	{
		TempStunPercent = CurrentStunPercent;
		ProgressBar_Stun->SetPercent(TempStunPercent);

		if (CurrentStunPercent <= 0)
			boss->bStunPossible = true;

		GetWorld()->GetTimerManager().ClearTimer(StunTimeHandle);
	}
}

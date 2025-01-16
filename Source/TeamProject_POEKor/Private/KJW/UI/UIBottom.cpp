// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/UI/UIBottom.h"
#include "KJW/UI/UIPlayerMain.h"
#include "KJW/ActorComponent/StatsActorComponent.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UUIBottom::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Eq->OnClicked.AddDynamic(this, &ThisClass::TogglePlayerInfo);
	Button_Inven->OnClicked.AddDynamic(this, &ThisClass::ToggleInven);
}
void UUIBottom::InitUI()
{
	APawn* PlayerPawn = GetOwningPlayer()->GetPawn();
	if (PlayerPawn)
	{
			UStatsActorComponent* StatsComponent = PlayerPawn->GetComponentByClass<UStatsActorComponent>();
			if (StatsComponent)
			{
				Stats = StatsComponent;
				Stats->UpdateHp.AddUObject(this, &ThisClass::SetHpOrb);
				Stats->UpdateMaxHp.AddUObject(this, &ThisClass::SetHpOrb);
				SetHpOrb();
			}
	
	}


}

void UUIBottom::SetMainUI(UUIPlayerMain* NewMainUI)
{
	MainUI = NewMainUI;
}

void UUIBottom::ToggleButton(EUIType UIType)
{
	if (MainUI)
	{
		MainUI->ToggleUI(UIType);
	}
}

void UUIBottom::TogglePlayerInfo()
{
	ToggleButton(EUIType::PlayerInfo);
}

void UUIBottom::ToggleInven()
{
	ToggleButton(EUIType::Inven);
}

void UUIBottom::SetHpOrb()
{
	if (Stats)
	{
		float Hp = Stats->GetHp();
		float MaxHp = Stats->GetMaxHp();
		
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

		if (HpTimeHandle.IsValid())
		{
			hpDelay = 0.f;
			//GetWorld()->GetTimerManager().ClearTimer(HpTimeHandle);
		}
		else
		{
			hpDelay = 0.f;
			GetWorld()->GetTimerManager().SetTimer(HpTimeHandle, this, &ThisClass::HpBarLerp, 0.02f, true);
		}

		
	}

}

void UUIBottom::HpBarLerp()
{
	hpDelay += 0.02f;
	TempHpPercent = FMath::Lerp(TempHpPercent, CurrentHpPercent, hpDelay);

	UE_LOG(LogTemp, Warning, TEXT("%f"), TempHpPercent);
	ProgressBar_Hp->SetPercent(TempHpPercent);

	if (FMath::IsNearlyEqual(TempHpPercent, CurrentHpPercent, 0.01f))
	{
		TempHpPercent = CurrentHpPercent;
		ProgressBar_Hp->SetPercent(TempHpPercent);
		GetWorld()->GetTimerManager().ClearTimer(HpTimeHandle);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"

#include "InteractionHintWidget.h"
#include "Components/CanvasPanelSlot.h"

void UMainHUDWidget::HideHint()
{
	if (InteractionHint)
	{
		InteractionHint->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainHUDWidget::SetHintPosition(const FVector2D& ScreenPosition)
{
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(InteractionHint->Slot);
	if (CanvasSlot)
	{
		CanvasSlot->SetPosition(ScreenPosition);
	}
}

void UMainHUDWidget::UpdateInteractionHint(const FText& HintText)
{
	if (InteractionHint)
	{
		if (HintText.IsEmpty())
		{
			InteractionHint->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			InteractionHint->SetVisibility(ESlateVisibility::Visible);
			InteractionHint->SetHintText(HintText);
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionHintWidget.h"
#include "Components/TextBlock.h"

void UInteractionHintWidget::SetHintText(const FText& InHintText)
{
	if (HintText)
	{
		HintText->SetText(InHintText);
	}
}
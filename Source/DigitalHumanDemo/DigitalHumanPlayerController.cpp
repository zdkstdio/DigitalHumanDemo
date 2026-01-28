// Fill out your copyright notice in the Description page of Project Settings.


#include "DigitalHumanPlayerController.h"

#include "MainHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.h"

void ADigitalHumanPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MainHUDClass)
	{
		MainHUDInstance = CreateWidget<UMainHUDWidget>(this, MainHUDClass);
		if (MainHUDInstance)
		{
			MainHUDInstance->AddToViewport();
		}
	}
}

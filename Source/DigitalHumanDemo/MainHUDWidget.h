// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

class UInteractionHintWidget;
/**
 * 
 */
UCLASS()
class DIGITALHUMANDEMO_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "InteractionHint")
	void HideHint();
	
	UFUNCTION(BlueprintCallable, Category = "InteractionHint")
	void SetHintPosition(const FVector2D& ScreenPosition);
	
	UFUNCTION(BlueprintCallable, Category = "InteractionHint")
	void UpdateInteractionHint(const FText& Text);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UInteractionHintWidget* InteractionHint;
};

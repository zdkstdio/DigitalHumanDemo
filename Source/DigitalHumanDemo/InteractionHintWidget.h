// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionHintWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DIGITALHUMANDEMO_API UInteractionHintWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "InteractionHint")
	void SetHintText(const FText& Text);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HintText;
};

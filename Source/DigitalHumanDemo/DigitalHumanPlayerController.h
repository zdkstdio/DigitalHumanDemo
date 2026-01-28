// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DigitalHumanPlayerController.generated.h"

class UMainHUDWidget;
/**
 * 
 */
UCLASS()
class DIGITALHUMANDEMO_API ADigitalHumanPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	UMainHUDWidget* GetMainHUD() const { return MainHUDInstance; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMainHUDWidget> MainHUDClass;

	UPROPERTY()
	UMainHUDWidget* MainHUDInstance;
};

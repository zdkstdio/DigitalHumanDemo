// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "DigitalHumanPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interactable.h"
#include "MainHUDWidget.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UInteractionComponent::TryInteract()
{
	if (!FocusedActor)
	{
		return;
	}

	if (UKismetSystemLibrary::DoesImplementInterface(FocusedActor, UInteractable::StaticClass()))
	{
		AActor* InstigatorActor = GetOwner();
		
		IInteractable::Execute_Interact(FocusedActor, InstigatorActor);
	}
}

FText UInteractionComponent::BuildInteractionHintText() const
{
	if (!FocusedActor)
	{
		return FText::GetEmpty();
	}

	if (!UKismetSystemLibrary::DoesImplementInterface(FocusedActor, UInteractable::StaticClass()))
	{
		return FText::GetEmpty();
	}
	
	return IInteractable::Execute_GetInteractionHintText(FocusedActor);
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	if (!Owner) return;

	APawn* PawnOwner = Cast<APawn>(Owner);

	const FVector Start = PawnOwner->GetActorLocation();
	const FVector End = Start + PawnOwner->GetActorForwardVector() * TraceDistance;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
	
	AActor* NewActor = Hit.GetActor();
	if (NewActor != FocusedActor)
	{
		FocusedActor = Hit.GetActor();
		NotifyInteractionTargetChanged();
	}
	
	if (bHit && Hit.GetActor())
	{
		// 获取Actor的屏幕坐标
		ADigitalHumanPlayerController* PlayerController = Cast<ADigitalHumanPlayerController>(PawnOwner->GetController());
		FVector2D ScreenPosition;
		bool bSuccess = PlayerController->ProjectWorldLocationToScreen(Hit.ImpactPoint, ScreenPosition);
		UMainHUDWidget* MainHUD = PlayerController->GetMainHUD();
		
		if (bSuccess && MainHUD)
		{
			MainHUD->SetHintPosition(ScreenPosition);
		}
		else
		{
			MainHUD->HideHint();
		}
		
		// 调试用：画射线、画命中点
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.f, 0, 1.f);
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 8.f, 12, FColor::Red, false, 0.f);
	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.f, 0, 1.f);
	}
}

void UInteractionComponent::NotifyInteractionTargetChanged()
{
	const FText HintText = BuildInteractionHintText();

	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!PawnOwner) return;

	ADigitalHumanPlayerController* PlayerController = Cast<ADigitalHumanPlayerController>(PawnOwner->GetController());
	if (!PlayerController) return;

	UMainHUDWidget* MainHUD = PlayerController->GetMainHUD();
	if (MainHUD)
	{
		MainHUD->UpdateInteractionHint(HintText);
	}
}


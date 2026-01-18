// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interactable.h"

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
	
	if (bHit && Hit.GetActor())
	{
		FocusedActor = Hit.GetActor();
		
		// 打日志输出 Actor 名称
		UE_LOG(LogTemp, Verbose, TEXT("Hit Actor: %s"), *FocusedActor->GetName());

		// 调试用：画射线、画命中点
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.f, 0, 1.f);
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 8.f, 12, FColor::Red, false, 0.f);
	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.f, 0, 1.f);
	}
}


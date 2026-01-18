// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Human.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInteractionComponent;

UCLASS()
class DIGITALHUMANDEMO_API AHuman : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHuman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void StartJump();
	void StopJump();

	void HandleInteract();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* HumanMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UInteractionComponent* InteractionComponent;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Human.h"

#include "InteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AHuman::AHuman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->DestroyComponent();
	
	HumanMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HumanMesh"));
	HumanMesh->SetupAttachment(RootComponent);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}

// Called when the game starts or when spawned
void AHuman::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHuman::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHuman::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AHuman::Turn(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void AHuman::LookUp(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void AHuman::StartJump()
{
	Jump();
}

void AHuman::StopJump()
{
	StopJumping();
}

void AHuman::HandleInteract()
{
	if (InteractionComponent)
	{
		InteractionComponent->TryInteract();
	}
}

// Called every frame
void AHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHuman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHuman::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHuman::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AHuman::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AHuman::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHuman::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHuman::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHuman::HandleInteract);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TankPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
#include "Player/PlayerPawn.h"

ATankPlayerController::ATankPlayerController()
{
	//bReplicates = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);

	PlayerPawn = Cast<APlayerPawn>(GetPawn());

	check(PlayerPawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATankPlayerController::Move);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATankPlayerController::Fire);
}

void ATankPlayerController::Move(const FInputActionValue& InputActionValue)
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	if(CursorHit.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), CursorHit.Location, 5.f, 10, FColor::Red, false, 2.f);
		PlayerPawn->MoveToLocation(CursorHit.Location);
	}
}

void ATankPlayerController::Fire(const FInputActionValue& InputActionValue)
{
	
}

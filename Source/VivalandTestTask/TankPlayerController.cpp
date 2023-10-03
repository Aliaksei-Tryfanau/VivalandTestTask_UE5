// Copyright Epic Games, Inc. All Rights Reserved.

#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TankCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ATankPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ATankPlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ATankPlayerController::OnFirePressed);
	}
}

void ATankPlayerController::OnInputStarted()
{
	StopMovement();
}

void ATankPlayerController::OnSetDestinationReleased()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	ServerRequestMove(Hit.Location);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Hit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void ATankPlayerController::OnFirePressed()
{
	if(ATankCharacter* PlayerCharacter = Cast<ATankCharacter>(GetPawn()))
	{
		PlayerCharacter->ServerFire();
	}
}

void ATankPlayerController::ServerRequestMove_Implementation(FVector_NetQuantize MovePoint)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MovePoint);
	ClientMoveToPosition(MovePoint);
}

void ATankPlayerController::ClientMoveToPosition_Implementation(FVector_NetQuantize MovePoint)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MovePoint);
}
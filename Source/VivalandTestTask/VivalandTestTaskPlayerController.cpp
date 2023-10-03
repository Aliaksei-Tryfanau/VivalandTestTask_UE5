// Copyright Epic Games, Inc. All Rights Reserved.

#include "VivalandTestTaskPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "VivalandTestTaskCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AVivalandTestTaskPlayerController::AVivalandTestTaskPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AVivalandTestTaskPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerCharacter = Cast<AVivalandTestTaskCharacter>(GetPawn());
}

void AVivalandTestTaskPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AVivalandTestTaskPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AVivalandTestTaskPlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AVivalandTestTaskPlayerController::OnFirePressed);
	}
}

void AVivalandTestTaskPlayerController::OnInputStarted()
{
	StopMovement();
}

void AVivalandTestTaskPlayerController::OnSetDestinationReleased()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	ServerRequestMove(Hit.Location);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Hit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void AVivalandTestTaskPlayerController::OnFirePressed()
{
	if(PlayerCharacter)
	{
		PlayerCharacter->ServerFire();
	}
}

void AVivalandTestTaskPlayerController::ServerRequestMove_Implementation(FVector_NetQuantize MovePoint)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MovePoint);
	ClientMoveToPosition(MovePoint);
}

void AVivalandTestTaskPlayerController::ClientMoveToPosition_Implementation(FVector_NetQuantize MovePoint)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MovePoint);
}
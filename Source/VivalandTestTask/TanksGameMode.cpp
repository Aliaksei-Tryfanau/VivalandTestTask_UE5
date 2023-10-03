// Copyright Epic Games, Inc. All Rights Reserved.

#include "TanksGameMode.h"
#include "TankPlayerController.h"
#include "TankCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATanksGameMode::ATanksGameMode()
{
	
}

void ATanksGameMode::Respawn(ACharacter* CharacterToRespawn, AController* ControllerToPossess)
{
	CharacterToRespawn->Reset();
	CharacterToRespawn->Destroy();
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
	int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
	RestartPlayerAtPlayerStart(ControllerToPossess, PlayerStarts[Selection]);
}

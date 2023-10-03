// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TankCharacter.h"
#include "TankPlayerController.generated.h"

class UNiagaraSystem;

UCLASS()
class ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputAction> FireAction;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	void OnInputStarted();
	void OnSetDestinationReleased();
	void OnFirePressed();

	UFUNCTION(Server, Reliable)
	void ServerRequestMove(FVector_NetQuantize MovePoint);

	UFUNCTION(Client, Reliable)
	void ClientMoveToPosition(FVector_NetQuantize MovePoint);
};



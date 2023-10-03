// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "VivalandTestTaskCharacter.h"
#include "VivalandTestTaskPlayerController.generated.h"

class UNiagaraSystem;

UCLASS()
class AVivalandTestTaskPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVivalandTestTaskPlayerController();

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
	UPROPERTY()
	TObjectPtr<AVivalandTestTaskCharacter> PlayerCharacter;

	void OnInputStarted();
	void OnSetDestinationReleased();
	void OnFirePressed();

	UFUNCTION(Server, Reliable)
	void ServerRequestMove(FVector_NetQuantize MovePoint);

	UFUNCTION(Client, Reliable)
	void ClientMoveToPosition(FVector_NetQuantize MovePoint);
};



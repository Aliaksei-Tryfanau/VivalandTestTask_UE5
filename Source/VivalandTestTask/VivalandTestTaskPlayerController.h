// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "VivalandTestTaskPlayerController.generated.h"

class UNiagaraSystem;

UCLASS()
class AVivalandTestTaskPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVivalandTestTaskPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

protected:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;
	
	void OnInputStarted();
	void OnSetDestinationReleased();
};



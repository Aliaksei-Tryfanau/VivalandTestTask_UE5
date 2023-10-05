// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TankPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class VIVALANDTESTTASK_API ATankPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATankPlayerState();
	void AddScore();

protected:
	virtual void OnRep_Score() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreWidget.h"
#include "GameFramework/HUD.h"
#include "TankHUD.generated.h"

/**
 * 
 */
UCLASS()
class VIVALANDTESTTASK_API ATankHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<UScoreWidget> TankOverlayClass;

	UPROPERTY()
	UScoreWidget* TankOverlay;

protected:
	virtual void BeginPlay() override;
};

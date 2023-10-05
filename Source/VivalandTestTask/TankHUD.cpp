// Fill out your copyright notice in the Description page of Project Settings.


#include "TankHUD.h"
#include "ScoreWidget.h"

void ATankHUD::BeginPlay()
{
	Super::BeginPlay();

	TankOverlay = CreateWidget<UScoreWidget>(GetWorld(), TankOverlayClass);

	if (TankOverlay != nullptr)
	{
		TankOverlay->AddToViewport();
	}
}

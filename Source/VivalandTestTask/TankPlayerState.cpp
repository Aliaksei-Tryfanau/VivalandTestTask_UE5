// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerState.h"
#include "ScoreWidget.h"
#include "TankHUD.h"

ATankPlayerState::ATankPlayerState()
{
	NetUpdateFrequency = 100.f;
}

void ATankPlayerState::AddScore()
{
	SetScore(GetScore() + 1);
	if(const APlayerController* Controller = GetPlayerController())
	{
		if(const ATankHUD* TankHUD = Cast<ATankHUD>(Controller->GetHUD()))
		{
			TankHUD->TankOverlay->UpdateScore();
		}
	}
}

void ATankPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	auto pawn = GetPawn();
	if(const APlayerController* Controller = GetPlayerController())
	{
		if(const ATankHUD* TankHUD = Cast<ATankHUD>(Controller->GetHUD()))
		{
			TankHUD->TankOverlay->UpdateScore();
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerState.h"
#include "ScoreWidget.h"
#include "TankHUD.h"
#include "Kismet/GameplayStatics.h"

ATankPlayerState::ATankPlayerState()
{
	NetUpdateFrequency = 100.f;
}

void ATankPlayerState::AddScore()
{
	SetScore(GetScore() + 1);
	if(const APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
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
	
	if(const APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if(const ATankHUD* TankHUD = Cast<ATankHUD>(Controller->GetHUD()))
		{
			TankHUD->TankOverlay->UpdateScore();
		}
	}
}

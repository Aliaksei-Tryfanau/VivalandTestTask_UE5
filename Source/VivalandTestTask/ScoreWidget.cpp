// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void UScoreWidget::UpdateScore()
{
	for (const APlayerState* Player : GetWorld()->GetGameState()->PlayerArray)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Player->GetScore()));
		if(Player->GetOwningController() == GetOwningPlayer())
		{
			PlayerScore->SetText(FText::FromString(ScoreText));
		}
		else
		{
			EnemyScore->SetText(FText::FromString(ScoreText));
		}
	}
}

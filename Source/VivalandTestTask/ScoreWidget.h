// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class VIVALANDTESTTASK_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayerScore;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* EnemyScore;
	
	void UpdateScore();
};

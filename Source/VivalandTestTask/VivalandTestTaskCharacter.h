// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VivalandTestTaskCharacter.generated.h"

UCLASS(Blueprintable)
class AVivalandTestTaskCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVivalandTestTaskCharacter();
	
	UFUNCTION(Server, Reliable)
	void ServerFire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFire();
};


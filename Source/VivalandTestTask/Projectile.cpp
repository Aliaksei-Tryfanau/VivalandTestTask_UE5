// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "TankCharacter.h"
#include "TankHUD.h"
#include "TankPlayerController.h"
#include "TankPlayerState.h"
#include "TanksGameMode.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->SetIsReplicated(true);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetOwner())
	{
		Destroy();
		return;
	}

	ACharacter* TankHit = Cast<ACharacter>(OtherActor);
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(GetInstigator()->GetController());
	if (TankHit && TankPlayerController)
	{
		if(ATankPlayerState* TankPlayerState = TankPlayerController->GetPlayerState<ATankPlayerState>())
		{
			TankPlayerState->AddScore();
		}
		
		if(ATanksGameMode* TanksGameMode = Cast<ATanksGameMode>(GetWorld()->GetAuthGameMode()))
		{
			TanksGameMode->Respawn(TankHit, TankHit->GetController());
		}
	}
	
	Destroy();
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "TestingGroundsProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	SetRootComponent(FP_Gun);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::OnFire() {
	// try and fire a projectile
	if (ProjectileClass != NULL) {
		UWorld* const World = GetWorld();
		if (World != NULL) {
			// Get the spawn transforms
			auto Controller = FP_Gun->GetAttachParent()->GetOwner()->GetInstigatorController();
			if (!Controller) { return; }
			const FRotator SpawnRotation = Controller->GetControlRotation(); //FP_Gun->GetSocketRotation(FName("Muzzle"));
			const FVector SpawnLocation = FP_Gun->GetSocketLocation(FName("Muzzle"));

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			ATestingGroundsProjectile* Projectile = World->SpawnActor<ATestingGroundsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			//Projectile->GetProjectileMovement()->Activate(); No need, auto activate.
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FirstPersonFireAnimation != NULL) {
		// Get the animation object for the arms mesh
		if (FirstPersonAnimInstance != NULL) {
			FirstPersonAnimInstance->Montage_Play(FirstPersonFireAnimation, 1.f);
		}
	}

	if (ThirdPersonAnimInstance != NULL) {
		// Get the animation object for the arms mesh
		if (ThirdPersonAnimInstance != NULL) {
			ThirdPersonAnimInstance->Montage_Play(ThirdPersonFireAnimation, 1.f);
		}
	}
}


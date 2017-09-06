// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	CastSphere(GetActorLocation(), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawnCount, int32 MaxSpawnCount) {
	/* Correctly find the World Transform bounds of this Tile. Down Left being the smallest and Top Right being the biggest.*/
	FVector Loc = GetActorLocation();
	FVector Min(Loc.X, Loc.Y - 2000, 0);
	FVector Max(Loc.X + 4000, Loc.Y + 2000, 0);

	FBox Bounds(Min, Max);

	int32 SpawnCount = FMath::RandRange(MinSpawnCount, MaxSpawnCount);

	for (size_t i = 0; i < SpawnCount; i++) {
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
			ActorToSpawn, 
			SpawnPoint, 
			FRotator(0)
		);

		if(!SpawnedActor) { return; }
		/* Keep the World Transform and not Relative Transform because we correctly spawn Actors in the World. */
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

bool ATile::CastSphere(FVector Location, float Radius) {
	FHitResult out_HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		out_HitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_Camera,
		FCollisionShape::MakeSphere(Radius)
	);

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, Radius, 100, ResultColor, true, 60);
	return HasHit;
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPoolComponent.h"


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
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetPool(UActorPoolComponent * InPool) {
	Pool = InPool;
}

/**
	Spawns the given actor type inside this tile a random number of times (between MinSpawnCount and MaxSpawnCount).
	May fail to place the actor as many times as promised if it can't find any empty locations.

	@param ActorToSpawn
	@param MinSpawnCount
	@param MaxSpawnCount
	@param Radius The radius of the Sphere we will search for hits in this Tile. (Should be as big as the actor we will spawn).
*/
void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawnCount, int32 MaxSpawnCount, float Radius) {

	int32 SpawnCount = FMath::RandRange(MinSpawnCount, MaxSpawnCount);

	for (size_t i = 0; i < SpawnCount; i++) {
		FVector out_SpawnPoint;
		bool Found = FindEmptyLocationInTile( out_SpawnPoint, Radius);

		if (Found) {
			// Generate a random yaw rotation
			float RandYawRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ActorToSpawn, out_SpawnPoint, FRotator(0, RandYawRotation, 0));
		}		
	}
}

/**
	Checks if anything overlaps a Sphere with radius Radius inside this Tile and 
	repeats until it finds an empty location or exceeds MAX_ATTEMPTS.

	@param Bounds The bounds in which we do the search.
	@param Radius The radius of the sphere.
	@param OutLocation The empty location out parameter.
	@return true if an empty location is found.
*/
bool ATile::FindEmptyLocationInTile(FVector& OutLocation, float Radius) {
	/* Correctly find the World Transform bounds of this Tile. Down Left point being the smallest and Top Right point being the biggest.*/
	FVector Loc = GetActorLocation();
	FVector Min(Loc.X, Loc.Y - 2000, 0);
	FVector Max(Loc.X + 4000, Loc.Y + 2000, 0);
	FBox Bounds(Min, Max);

	bool HasHit = true;
	const int32 MAX_ATTEMPTS = 100;

	for (size_t i = 0; i < MAX_ATTEMPTS; i++) {
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		HasHit = CastSphere(SpawnPoint, Radius);
		if (!HasHit) {
			OutLocation = SpawnPoint;
			return true;
		}
	}

	return false;
}

/**
	Checks if anything overlaps a Sphere with radius Radius.

	@param Location The location to cast the sphere.
	@param Radius The radius of the sphere.
	@return true if the sphere doesn't overlap anything.
*/
bool ATile::CastSphere(FVector Location, float Radius) {
	FHitResult out_HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		out_HitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // SpawnChannel
		FCollisionShape::MakeSphere(Radius)
	);

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, ResultColor, true, 50);
	return HasHit;
}

/**
	Spawns the given actor type at SpawnPoint and attaches it to this tile.

	@param ActorToSpawn
	@param SpawnPoint
*/
void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector SpawnPoint, FRotator SpawnRotation) {
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ActorToSpawn,
		SpawnPoint,
		SpawnRotation
	);

	if (!SpawnedActor) { return; }
	/* Keep the World Transform and not Relative Transform because we correctly spawn Actors in the World. */
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}


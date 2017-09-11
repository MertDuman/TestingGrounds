// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawnCount = 1, int32 MaxSpawnCount = 1, float Radius = 300.f);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(class UActorPoolComponent* InPool);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void GetNavMeshFromPoolAndReposition();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void ReturnNavMeshToPool();

private:
	bool CastSphere( FVector Location, float Radius = 300);

	bool FindEmptyLocationInTile( FVector& OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector SpawnPoint, FRotator SpawnRotation);

	void PlaceAI(TSubclassOf<APawn> PawnToSpawn, FVector SpawnPoint, FRotator SpawnRotation);

	UActorPoolComponent* Pool;

	AActor* NavMeshBoundsVolume;
	
};

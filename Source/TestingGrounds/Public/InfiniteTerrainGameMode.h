// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

public:
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void FindAllNavMeshBoundsVolumes();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPoolComponent* NavMeshBoundsVolumePool;

	
private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);
};

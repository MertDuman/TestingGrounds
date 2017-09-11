// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "ActorPoolComponent.h"
#include "EngineUtils.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() {
	ActorPoolComponent = CreateDefaultSubobject<UActorPoolComponent>(FName("ActorPoolComponent"));
}

void AInfiniteTerrainGameMode::FindAllNavMeshBoundsVolumes() {
	TActorIterator<ANavMeshBoundsVolume> NavMeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (NavMeshIterator) {
		AddToPool(*NavMeshIterator);
		++NavMeshIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume * VolumeToAdd) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *VolumeToAdd->GetName());
	ActorPoolComponent->Add(VolumeToAdd);
}



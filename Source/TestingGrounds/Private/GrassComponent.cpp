// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"


UGrassComponent::UGrassComponent() {
	SetCollisionProfileName(FName("OverlapAllDynamic"));
}

void UGrassComponent::BeginPlay() {
	Super::BeginPlay();

	SpawnGrass();
}

void UGrassComponent::SpawnGrass() {
	for (size_t i = 0; i < SpawnCount; i++) {
		FVector SpawnLocation = FMath::RandPointInBox(Bounds);
		AddInstance(FTransform(SpawnLocation));
	}
}

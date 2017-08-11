// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolRouteComponent.h"


// Sets default values for this component's properties
UPatrolRouteComponent::UPatrolRouteComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPatrolRouteComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPatrolRouteComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

TArray<ATargetPoint*> UPatrolRouteComponent::GetPatrolPoints() const {
	return PatrolPoints;
}


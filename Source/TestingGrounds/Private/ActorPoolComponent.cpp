// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPoolComponent.h"


// Sets default values for this component's properties
UActorPoolComponent::UActorPoolComponent()
{

}


// Called when the game starts
void UActorPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

AActor* UActorPoolComponent::Checkout() {
	return nullptr;
}

void UActorPoolComponent::Return(AActor* ActorToReturn) {

}

void UActorPoolComponent::Add(AActor* ActorToAdd) {

}


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
	if ( Pool.Num() == 0) { 
		UE_LOG(LogTemp, Warning, TEXT("[%s - Checkout()] Pool is empty."), *GetName());
		return nullptr; 
	}
	return Pool.Pop();
}

void UActorPoolComponent::Return(AActor* ActorToReturn) {
	Pool.Push( ActorToReturn);
}

void UActorPoolComponent::Add(AActor* ActorToAdd) {
	Return( ActorToAdd);
}


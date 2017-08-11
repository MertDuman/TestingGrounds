// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TargetPoint.h"
#include "PatrolRouteComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrolRouteComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<ATargetPoint*> GetPatrolPoints() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<ATargetPoint*> PatrolPoints;
		
	
};

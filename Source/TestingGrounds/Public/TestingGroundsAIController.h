// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestingGroundsAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API ATestingGroundsAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATestingGroundsAIController();

protected:
	virtual void BeginPlay() override;
	
};

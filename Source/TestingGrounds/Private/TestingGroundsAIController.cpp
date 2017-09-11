// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGroundsAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ATestingGroundsAIController::ATestingGroundsAIController() {
	SetGenericTeamId(FGenericTeamId(1));
}

void ATestingGroundsAIController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("%i"), GetGenericTeamId().GetId());

	ETeamAttitude::Type TeamAttitude = GetTeamAttitudeTowards( *this);
	if (TeamAttitude == ETeamAttitude::Friendly) {
		UE_LOG(LogTemp, Warning, TEXT("Friendly"));
	}
	if (TeamAttitude == ETeamAttitude::Hostile) {
		UE_LOG(LogTemp, Warning, TEXT("Hostile"));
	}
	if (TeamAttitude == ETeamAttitude::Neutral) {
		UE_LOG(LogTemp, Warning, TEXT("Neutral"));
	}
}



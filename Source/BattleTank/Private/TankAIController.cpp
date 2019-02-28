// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	
	if (PlayerTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->FunctionTembakDariCPP();
	}
}





void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

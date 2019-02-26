// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	ATank* PlayerTank = nullptr;
	PlayerTank = GetPlayerTank();
	
	if (PlayerTank) {
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
}

ATank*	ATankAIController::GetControlledTank() const{
	return Cast<ATank>(GetPawn());
}


ATank * ATankAIController::GetPlayerTank() const
{
	ATankPlayerController* Tpc = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	return Cast<ATank>(Tpc->GetPawn());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not possesed the Tank"));
	}
	else {
		auto PlayerTank = GetPlayerTank();
		if (!PlayerTank) {
			UE_LOG(LogTemp, Warning, TEXT("AI Controller possesed: %s and cant find what to kill"), *ControlledTank->GetName());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("AI Controller possesed: %s And Want to Kill: %s"), *ControlledTank->GetName(), *PlayerTank->GetName());

		}
		
	}
}

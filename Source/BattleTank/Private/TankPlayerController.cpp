// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay(){
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not possesed the Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possesed: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector OutHitLocation; //would be modified by GetSightRayHitLocation
	if (GetSightRayHitLocation(OutHitLocation)) {

	}
}

void ATankPlayerController::AimTowardTheCrosshair(){
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; //ini out parameter
	if (GetSightRayHitLocation(OutHitLocation)) {

	}
}

//return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXPosition, ViewportSizeY*CrosshairYPosition);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *LookDirection.ToString());
	}
	return true;
}



bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector WorldDirection;//ora butuh var iki, cuma butuh ngerti LookDirection
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, LookDirection, WorldDirection);
}

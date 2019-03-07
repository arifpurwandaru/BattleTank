// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay(){
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
		FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardTheCrosshair();
}

void ATankPlayerController::AimTowardTheCrosshair(){
	if (!ensure(GetControlledTank())) { return; }

	FVector OutHitLocation; //ini out parameter
	if (GetSightRayHitLocation(OutHitLocation)) {
		UTankAimingComponent* TankAimingComponent = nullptr;
		TankAimingComponent = GetControlledTank()->GetTankAimingComponent();
		if (!ensure(TankAimingComponent)) { return; }


		TankAimingComponent->AimAt(OutHitLocation);
	
	}
}

//return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXPosition, ViewportSizeY*CrosshairYPosition);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation;//ora butuh var iki, cuma butuh ngerti LookDirection
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
				HitResult,
				StartLocation,
				EndLocation,
				ECollisionChannel::ECC_Visibility)
		) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}


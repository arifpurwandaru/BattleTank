// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PistulBarel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetKomponenPistul(UPistulBarel * PistulToSet){
	Pistul = PistulToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float KecepatanPelor) {
	if (!Pistul) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Pistul->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		KecepatanPelor,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) {
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			GerakakenPistule(AimDirection);
	}
	
	
		
}

void UTankAimingComponent::GerakakenPistule(FVector AimDirection) {
	//Work-out difference between current barrel (pistul) rotation and AimDirection
	auto PistulRotator = Pistul->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - PistulRotator;
	Pistul->Elevate(DeltaRotator.Pitch);
}

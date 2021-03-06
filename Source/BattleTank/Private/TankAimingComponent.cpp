// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PistulBarel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	LastReloaded = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastReloaded) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Pistul)) { return false; }
	auto BarrelForward = Pistul->GetForwardVector();

	return !BarrelForward.Equals(AimDirection,0.01);
}


void UTankAimingComponent::Initialize(UPistulBarel * PistulToSet, UTankTurret * TurretToSet) {
	Pistul = PistulToSet;
	TankTurret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Pistul)) { return; }
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
			AimDirection = OutLaunchVelocity.GetSafeNormal();
			GerakakenPistule(AimDirection);
	}
	
	
		
}




void UTankAimingComponent::GerakakenPistule(FVector AimDirection) {
	//Work-out difference between current barrel (pistul) rotation and AimDirection
	auto PistulRotator = Pistul->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - PistulRotator;
	Pistul->Elevate(DeltaRotator.Pitch);
	TankTurret->Mubeng(DeltaRotator.Yaw);
}


bool UTankAimingComponent::FunctionTembakDariCPP() {
	if (!ensure(ProjectileBlueprint)) { return false; }
	
	//bool isReloaded = (FPlatformTime::Seconds() - LastReloaded) > ReloadTimeInSeconds;

	if (FiringState != EFiringState::Reloading){
		//Nyepawn peluru dari socketnya barrel yg bernama "Projectile" => liat socket di static mesh barrel
		auto Peluru = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Pistul->GetSocketLocation(FName("Projectile")),
			Pistul->GetSocketRotation(FName("Projectile"))
			);

		Peluru->LuncurkanPeluru(KecepatanPelor);

		LastReloaded = FPlatformTime::Seconds();
		return true;
	}
	return false;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

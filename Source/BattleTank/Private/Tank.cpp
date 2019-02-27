// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "PistulBarel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ATank::AimAt(FVector vector){
	TankAimingComponent->AimAt(vector,KecepatanPelor);
}

void ATank::SetPistulReference(UPistulBarel * PistulToSet){
	TankAimingComponent->SetKomponenPistul(PistulToSet);
	LocalBarelToShoot = PistulToSet;
}

void ATank::SetTankTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTankTurrent(TurretToSet);
}


void ATank::FunctionTembakDariCPP(){
	if (!LocalBarelToShoot) { return; }

	auto Peluru = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		LocalBarelToShoot->GetSocketLocation(FName("Projectile")),
		LocalBarelToShoot->GetSocketRotation(FName("Projectile"))
		);

	Peluru->LuncurkanPeluru(KecepatanPelor);
}

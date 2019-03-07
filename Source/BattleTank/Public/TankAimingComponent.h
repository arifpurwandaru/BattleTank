// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};

//forward declaration
class UPistulBarel; 
class UTankTurret;

//The Aiming Component
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetKomponenPistul(UPistulBarel* PistulToSet);
	void SetTankTurrent(UTankTurret* TurretToSet);
	void AimAt(FVector HitLocation, float KecepatanPelor);
	 
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UPistulBarel* Pistul = nullptr;
	UTankTurret* TankTurret = nullptr;

	void GerakakenPistule(FVector AimDirection);
		
};

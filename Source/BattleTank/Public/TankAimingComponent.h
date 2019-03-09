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
class AProjectile;

//The Aiming Component
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UPistulBarel* PistulToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
	bool FunctionTembakDariCPP();

	EFiringState GetFiringState() const;

	 
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();


	UPistulBarel* Pistul = nullptr;
	UTankTurret* TankTurret = nullptr;

	double LastReloaded = 0;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float KecepatanPelor = 5000; //50 m/s

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ReloadTimeInSeconds = 3;

	void GerakakenPistule(FVector AimDirection);

	FVector AimDirection;

		
};

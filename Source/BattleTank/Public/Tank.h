// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward Declaration
class UPistulBarel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector vector);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetPistulReference(UPistulBarel* PistulToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
	bool FunctionTembakDariCPP();

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float KecepatanPelor = 5000; //50 m/s

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Setup)
		float ReloadTimeInSeconds = 3;

	UPistulBarel* LocalBarelToShoot = nullptr;

	double LastReloaded = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//forward declaration
class UPistulBarel; 

//The Aiming Component
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetKomponenPistul(UPistulBarel* PistulToSet);
	void AimAt(FVector HitLocation, float KecepatanPelor);
	 


private:
	UPistulBarel* Pistul = nullptr;
	void GerakakenPistule(FVector AimDirection);
		
};

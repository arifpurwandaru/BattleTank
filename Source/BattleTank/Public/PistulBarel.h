// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PistulBarel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UPistulBarel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 5 ;
	UPROPERTY(EditAnywhere)
		float MinElevation = 0;
	UPROPERTY(EditAnywhere)
		float MaxElevation = 40;
	
};

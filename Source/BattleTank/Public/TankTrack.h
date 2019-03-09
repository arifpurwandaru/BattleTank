// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Input")
	void SetThrottle(float Throttle);


	//Force atau daya dalam newtons, F=m*a
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 32707000; //karena tank massa nya 40kg

private:
	UTankTrack();
	virtual void BeginPlay() override;

	void ApplySidewayForce();
	void DriveTrack();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0;
};

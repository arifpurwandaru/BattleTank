// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType, ThisTickFunction);
	
	//begin: beberapa code dibawah ini supaya gak ngedrift
	
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	//calculate and apply sideways (F=m.a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()* CorrectionAcceleration) /2; //2 tracks
	TankRoot->AddForce(CorrectionForce);


}
void UTankTrack::SetThrottle(float Throttle) {
	
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //lokasi rantai roda penggerak (tankTrack)
	
	//tank root adalah parentnya TankTrack which is instance tank itu sendiri
	//dicast menjadi UPrimitiveComponents (mbahnya staticmeshcomponent) karena kalo ga dicast
	//dia otomatis jadi SceneComponent (mbah buyute staticmeshcomponent) dan tidak bisa diapply force
	//(di AddForceAtLocation)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
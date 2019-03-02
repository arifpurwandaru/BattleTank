// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

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
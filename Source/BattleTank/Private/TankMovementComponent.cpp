// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet) {
	if (!RightTrackToSet || !LeftTrackToSet) { return; }
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}
void UTankMovementComponent::IntendMoveForward(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}

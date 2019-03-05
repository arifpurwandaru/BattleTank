// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet) {
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}
void UTankMovementComponent::IntendMoveForward(float Throw) {
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendMoveKananKirik(float Throw) {
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(-Throw);
}
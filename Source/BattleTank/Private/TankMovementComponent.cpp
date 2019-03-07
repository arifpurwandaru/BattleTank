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

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed){
	//no need to call Super as we're replacing the functionality

	//auto TankName = GetOwner()->GetName();
	

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	//Untuk lebih jelasnya lihat udemy course section 4, Lecture 172 DotProduct() vector operator
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	//Untuk lebih jelasnya lihat udemy course section 4, Lecture 173 CrossProduct() vector operator
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *AIForwardIntention.ToString());
		IntendMoveForward(ForwardThrow);
		IntendMoveKananKirik(RightThrow);


}

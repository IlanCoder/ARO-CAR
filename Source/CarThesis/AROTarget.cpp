// Fill out your copyright notice in the Description page of Project Settings.

#include "AROTarget.h"
#include <GameFramework/Actor.h>

UAROTarget::UAROTarget() {
	PrimaryComponentTick.bCanEverTick = true;
	myBoss = GetOwner();
}

void UAROTarget::BeginPlay() {
	Super::BeginPlay();
}

void UAROTarget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CalculateForces(DeltaTime);
	myBoss->SetActorLocation(myBoss->GetActorLocation() + velocity, true);
	ResetExternalForces();
}

void UAROTarget::SetExternalForce(FVector force) {
	externalForces.Push(force);
}

void UAROTarget::ResetExternalForces() {
	externalForces.Empty();
}

void UAROTarget::CalculateForces(float DeltaTime) {
	for (int force = 0; force < externalForces.Num(); ++force) {
		velocity += externalForces[force] * DeltaTime;
	}
}

void UAROTarget::SetVelocity(FVector newVelocity) {
	velocity = newVelocity;
}

FVector UAROTarget::GetVelocity() {
	return velocity;
}
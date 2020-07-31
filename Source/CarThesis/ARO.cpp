// Fill out your copyright notice in the Description page of Project Settings.

#include "ARO.h"

AARO::AARO() {
	PrimaryActorTick.bCanEverTick = true;
}

void AARO::BeginPlay() {
	Super::BeginPlay();
	SetFormulaConstants();
	SetArraysSize();
	SetTargetAROArray();
}

void AARO::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	for (int object = 0; object < affectedObjects.Num(); ++object) {
		CalculateDirection(object);
		currentDistance[object] = forceVectorDirection[object].Size();
		CalculateAcceleration(object);
		forceVectorDirection[object].Normalize();
		SendAccelerations(object);
	}
}

void AARO::CalculateDirection(int obj) {
	if (!repulsion) {
		forceVectorDirection[obj] = GetActorLocation() - affectedObjects[obj]->GetActorLocation();
	} else {
		forceVectorDirection[obj] = affectedObjects[obj]->GetActorLocation() - GetActorLocation();
	}
}

void AARO::CalculateAcceleration(int obj) {
	if (currentDistance[obj] < minDistance) {
		acceleration[obj] = force;
	} else if (currentDistance[obj] > maxDistance) {
		acceleration[obj] = 0;
	} else {
		acceleration[obj] = force * (maxDistDivision - (1 / currentDistance[obj])) / forceDivision;
	}
	if (acceleration[obj] < 0) {
		acceleration[obj] = 0;
	}
}

void AARO::SendAccelerations(int obj) {
	if (acceleration[obj] > 0) {
		targetAROComponent[obj]->SetExternalForce(forceVectorDirection[obj] * acceleration[obj]);
	}
}

void AARO::SetFormulaConstants() {
	if (minDistance <= 0) {
		minDistance = 0.1f;
	}
	if (maxDistance <= minDistance) {
		maxDistance = minDistance + 0.1f;
	}
	maxDistDivision = 1 / FMath::Square(maxDistance);
	forceDivision = maxDistDivision - (1 / FMath::Square(minDistance));
}

void AARO::SetArraysSize() {
	forceVectorDirection.SetNumZeroed(affectedObjects.Num());
	forceVector.SetNumZeroed(affectedObjects.Num());;
	currentDistance.SetNumZeroed(affectedObjects.Num());;
	acceleration.SetNumZeroed(affectedObjects.Num());;
	targetAROComponent.SetNumZeroed(affectedObjects.Num());
}

void AARO::SetTargetAROArray() {
	UActorComponent* tempTargetComp;
	for (int object = 0; object < affectedObjects.Num(); ++object) {
		tempTargetComp = affectedObjects[object]->GetComponentByClass(UAROTarget::StaticClass());
		if (tempTargetComp != nullptr) {
			targetAROComponent[object] = Cast<UAROTarget>(tempTargetComp);
		}
	}
}

void AARO::SetNew(float newMinDistance, float newMaxDistance, int newForce, bool newRepulsion, TArray<AActor*> newAffectedObjects) {
	minDistance = newMinDistance;
	maxDistance = newMaxDistance;
	force = newForce;
	repulsion = newRepulsion;
	affectedObjects = newAffectedObjects;
	SetFormulaConstants();
	SetArraysSize();
	SetTargetAROArray();
}

void AARO::AddAffectedObject(AActor* newObject) {
	forceVectorDirection.Push(FVector(0, 0, 0));
	forceVector.Push(FVector(0, 0, 0));
	currentDistance.Push(0);
	acceleration.Push(0);
	affectedObjects.Push(newObject);
	UActorComponent* tempTargetComp = affectedObjects[affectedObjects.Num() - 1]->GetComponentByClass(UAROTarget::StaticClass());
	if (tempTargetComp != nullptr) {
		targetAROComponent.Push(Cast<UAROTarget>(tempTargetComp));
	}
}

void AARO::RemoveAffectedObject(AActor* targetObject) {
	int removeHeader = affectedObjects.Find(targetObject);
	affectedObjects.RemoveAt(removeHeader);
	targetAROComponent.RemoveAt(removeHeader);
	forceVector.Pop();
	forceVectorDirection.Pop();
	currentDistance.Pop();
	acceleration.Pop();
}
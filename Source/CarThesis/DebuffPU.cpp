// Fill out your copyright notice in the Description page of Project Settings.

#include "DebuffPU.h"
#include <Runtime/Engine/Classes/Engine/World.h>

void ADebuffPU::SetTargetAROs() {
	FindTargets();
	powerUpARO.SetNumZeroed(AROAffectedObjects.Num());
	for (int targetNum = 0; targetNum < powerUpARO.Num(); ++targetNum) {
		if (AROAffectedObjects[targetNum] != nullptr) {
			SpawnARO(targetNum);
		}
	}
}

void ADebuffPU::SpawnARO(int AROHeader) {
	powerUpARO[AROHeader] = GetWorld()->SpawnActor<AARO>(AROSpawn, FVector::ForwardVector * -100, FRotator::ZeroRotator);
	powerUpARO[AROHeader]->AttachToActor(AROAffectedObjects[AROHeader], FAttachmentTransformRules::KeepRelativeTransform);
	Super::SpawnARO(AROHeader);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "AuraPU.h"
#include <Runtime/Engine/Classes/Engine/World.h>

void AAuraPU::SpawnARO(int AROHeader) {	
	powerUpARO[AROHeader] = GetWorld()->SpawnActor<AARO>(AROSpawn, FVector::ZeroVector, FRotator::ZeroRotator);
	powerUpARO[AROHeader]->AttachToActor(throwerPlayer, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Super::SpawnARO(AROHeader);
}
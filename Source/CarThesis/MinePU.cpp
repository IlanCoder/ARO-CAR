// Fill out your copyright notice in the Description page of Project Settings.

#include "MinePU.h"
#include <Runtime/Engine/Classes/Engine/World.h>

void AMinePU::SpawnARO(int AROHeader) {
	powerUpARO[AROHeader] = GetWorld()->SpawnActor<AARO>(AROSpawn, throwerPlayer->GetActorLocation(), FRotator::ZeroRotator);
	Super::SpawnARO(AROHeader);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "MissilePU.h"
#include <Runtime/Engine/Classes/Engine/World.h>

void AMissilePU::Tick(float DeltaTime) {
	powerUpARO[0]->SetActorLocation(powerUpARO[0]->GetActorLocation() + fireDirection*missileSpeed);
	Super::Tick(DeltaTime);
}

void AMissilePU::SpawnARO(int AROHeader) {
	fireDirection = throwerPlayer->GetActorForwardVector();
	powerUpARO[AROHeader] = GetWorld()->SpawnActor<AARO>(AROSpawn, throwerPlayer->GetActorLocation(), FRotator::ZeroRotator);
	Super::SpawnARO(AROHeader);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffPU.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <EngineUtils.h>

void ABuffPU::SpawnARO(int AROHeader) {
	powerUpARO[AROHeader] = GetWorld()->SpawnActor<AARO>(AROSpawn, FVector::ForwardVector * 100, FRotator::ZeroRotator);
	powerUpARO[AROHeader]->AttachToActor(throwerPlayer, FAttachmentTransformRules::KeepRelativeTransform);
	Super::SpawnARO(AROHeader);
}

void ABuffPU::FindTargets() {
	for (TActorIterator<AActor> actorItr(GetWorld()); actorItr; ++actorItr) {
		AActor* actor = *actorItr;
		if (actor->GetComponentByClass(UAROTarget::StaticClass()) != nullptr && !AROAffectedObjects.Contains(actor) && actor == throwerPlayer) {
			AROAffectedObjects.Push(actor);
		}
		break;
	}
}
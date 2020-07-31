// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUp.h"
#include <EngineUtils.h>

APowerUp::APowerUp() {
	PrimaryActorTick.bCanEverTick = true;
}

void APowerUp::BeginPlay() {
	Super::BeginPlay();
	lifeTimeLeft = lifeTime;
}

void APowerUp::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	lifeTimeLeft -= DeltaTime;
	if (lifeTimeLeft <= 0) {
		Destructor();
	}
}

void APowerUp::SpawnARO(int AROHeader) {
	powerUpARO[AROHeader]->SetNew(AROMinDistance, AROMaxDistance, AROForce, ARORepulsion, AROAffectedObjects);
}

void APowerUp::Destructor() {
	for (int currentARO = powerUpARO.Num() - 1; currentARO >= 0; --currentARO) {
		powerUpARO[currentARO]->Destroy();
	}	
	Destroy();
}

void APowerUp::SetTargetAROs() {
	FindTargets();
	powerUpARO.SetNumZeroed(1);
	if (throwerPlayer != nullptr) {
		SpawnARO(0);
	}
}

void APowerUp::FindTargets() {
	for (TActorIterator<AActor> actorItr(GetWorld()); actorItr; ++actorItr) {
		AActor* actor = *actorItr;
		if (actor->GetComponentByClass(UAROTarget::StaticClass()) != nullptr && !AROAffectedObjects.Contains(actor) && actor != throwerPlayer) {
			AROAffectedObjects.Push(actor);
		}
	}
}

void APowerUp::SetThrowerPlayer(AActor* throwerPlayer) {
	this->throwerPlayer = throwerPlayer;
	SetTargetAROs();
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"

AGameManager::AGameManager() {
	PrimaryActorTick.bCanEverTick = true;

}

void AGameManager::BeginPlay() {
	Super::BeginPlay();
	
}

void AGameManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
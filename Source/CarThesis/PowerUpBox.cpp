// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpBox.h"
#include "PlayerCar.h"

APowerUpBox::APowerUpBox() {
	PrimaryActorTick.bCanEverTick = true;
}

void APowerUpBox::BeginPlay() {
	Super::BeginPlay();
	disabledTime = 0;
}

void APowerUpBox::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	disabledTime -= DeltaTime;
	if (disabledTime <= 0) {
		Appear();
	}
}

void APowerUpBox::OnCollision(AActor* collidingActor) {
	APlayerCar* collidingActorCast = Cast<APlayerCar>(collidingActor);
	if (collidingActor != nullptr) {
		int powerUpNumber = FMath::RandRange(0, powerUpList.Num() - 1);
		collidingActorCast->AddPowerUp(powerUpList[powerUpNumber]);
	}
	Disappear();
}

void APowerUpBox::Disappear() {
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(true);
	disabledTime = 5;
}

void APowerUpBox::Appear() {
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(false);
}
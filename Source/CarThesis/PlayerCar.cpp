// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCar.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <Components/InputComponent.h>

APlayerCar::APlayerCar() {
	PrimaryActorTick.bCanEverTick = true;
	alive = true;
}

void APlayerCar::BeginPlay() {
	Super::BeginPlay();
	GetAROTargetComponent();
	respawnPos = GetActorLocation();
	respawnRot = GetActorRotation();
}

void APlayerCar::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (acceleratorARO != nullptr) {
		AceleratorAROManager();
	}
	if (breakARO != nullptr) {
		BreakAROManager();
	}
	if (alive) {
		lookAt *= DeltaTime;
		RotationManager();
	} else {
		respawnTime -= DeltaTime;
		if (respawnTime <= 0) {
			Respawn();
		}
	}
}

void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCar::AfterCrashVelocity(FVector collisionNormal) {
	if (alive) {
		FVector playerVelocity = myAROTargetComponent->GetVelocity();
		playerLife -= (playerVelocity.GetAbs() * collisionNormal.GetAbs()).Size();	
		if (playerLife <= 0) {
			Kill();
		}
		FVector newVelocity;
		float dotProduct = FVector::DotProduct(playerVelocity, collisionNormal);
		if (dotProduct <= 0) {
			newVelocity = playerVelocity - 1.1f * dotProduct * collisionNormal;
		} else {
			newVelocity = playerVelocity + 0.1f * collisionNormal;
		}
		myAROTargetComponent->SetVelocity(newVelocity);
	}
}

void APlayerCar::Accelerate(float axisValue) {
	if (!alive) { axisValue = 0; }
	if (axisValue >= 0) {
		acceleratorAROLocation.X = 201 - axisValue * 100;
	}
}

void APlayerCar::CarBreak(float axisValue) {
	if (!alive) { axisValue = 0; }
	if (axisValue >= 0) {
		breakAROLocation.X = -201 + axisValue * 100;
	}
}

void APlayerCar::Right(float axisValue) {
	lookAt.Yaw = axisValue * rotateSpeed;
}

void APlayerCar::Up(float axisValue) {
	lookAt.Pitch = axisValue * rotateSpeed;
}

void APlayerCar::Rotate(float axisValue) {
	lookAt.Roll = axisValue * rotateSpeed;
}

void APlayerCar::GetAROTargetComponent() {
	UActorComponent* tempTargetComp;
	tempTargetComp = GetComponentByClass(UAROTarget::StaticClass());
	if (tempTargetComp != nullptr) {
		myAROTargetComponent = Cast<UAROTarget>(tempTargetComp);
	}
}

void APlayerCar::RotationManager() {
	playerTransform = GetActorTransform();
	playerTransform.ConcatenateRotation(lookAt.Quaternion());
	playerTransform.NormalizeRotation();
	SetActorTransform(playerTransform);
}

void APlayerCar::BreakAROManager() {
	if (breakAROLocation.X > -201) {
		breakForceVector = myAROTargetComponent->GetVelocity();
		breakARO->force = breakForceVector.Size() / breakForce;
		if (breakARO->force < 0.05f) {
			myAROTargetComponent->SetVelocity(myAROTargetComponent->GetVelocity() *= 0);
		}
		if (!breakForceVector.IsZero()) {
			breakForceVector.Normalize();
			breakForceVector *= breakAROLocation.X;
			breakARO->SetActorLocation(GetActorLocation() + breakForceVector);
		}
	} else {
		breakARO->SetActorRelativeLocation(breakAROLocation);
	}
}

void APlayerCar::AceleratorAROManager() {
	acceleratorARO->SetActorRelativeLocation(acceleratorAROLocation);
}

void APlayerCar::AddPowerUp(TSubclassOf<APowerUp> newPowerUp) {
	powerUp = newPowerUp;
}

void APlayerCar::SpawnPowerUp() {
	if (powerUp != nullptr) {
		APowerUp* thrownPower = GetWorld()->SpawnActor<APowerUp>(powerUp, FVector::ZeroVector, FRotator::ZeroRotator);
		thrownPower->SetThrowerPlayer(this);
		powerUp = nullptr;
	}
}

void APlayerCar::Kill() {
	alive = false;
	respawnTime = 5;
}

void APlayerCar::Respawn() {
	SetActorLocation(respawnPos);
	SetActorRotation(respawnRot);
	myAROTargetComponent->SetVelocity(FVector::ZeroVector);
	playerLife = 100;
	alive = true;
}

void APlayerCar::SetCheckpoint(FVector position, FRotator rotation) {
	respawnPos = position;
	respawnRot = rotation;
}
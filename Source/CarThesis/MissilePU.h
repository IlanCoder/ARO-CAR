// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "MissilePU.generated.h"

/**
 * 
 */
UCLASS()
class CARTHESIS_API AMissilePU : public APowerUp
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	float missileSpeed;
	FVector fireDirection;
	void Tick(float DeltaTime) override;
	void SpawnARO(int AROHeader) override;
};

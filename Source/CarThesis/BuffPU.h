// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "BuffPU.generated.h"

/**
 * 
 */
UCLASS()
class CARTHESIS_API ABuffPU : public APowerUp
{
	GENERATED_BODY()
private:
	void SpawnARO(int AROHeader) override;
	void FindTargets() override;
};

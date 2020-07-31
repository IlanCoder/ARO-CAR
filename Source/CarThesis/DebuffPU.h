// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "DebuffPU.generated.h"

/**
 * 
 */
UCLASS()
class CARTHESIS_API ADebuffPU : public APowerUp
{
	GENERATED_BODY()
private:
	void SetTargetAROs() override;
	void SpawnARO(int AROHeader) override;
};

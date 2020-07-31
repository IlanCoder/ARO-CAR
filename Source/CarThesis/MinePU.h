// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "MinePU.generated.h"

/**
 * 
 */
UCLASS()
class CARTHESIS_API AMinePU : public APowerUp
{
	GENERATED_BODY()
private:
	void SpawnARO(int AROHeader) override;
};

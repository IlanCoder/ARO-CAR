// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class CARTHESIS_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

protected:
	virtual void BeginPlay() override;
	TArray<TSubclassOf<AActor*>> checkpoints;
public:	
	virtual void Tick(float DeltaTime) override;

	
	
};

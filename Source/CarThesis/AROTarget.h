// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AROTarget.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARTHESIS_API UAROTarget : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAROTarget();

protected:
	virtual void BeginPlay() override;
	TArray<FVector> externalForces;
	AActor* myBoss;
	void ResetExternalForces();
	void CalculateForces(float DeltaTime);
	UPROPERTY(EditAnywhere)
	FVector velocity;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetExternalForce(FVector force);
	void SetVelocity(FVector newVelocity);
	FVector GetVelocity();
};

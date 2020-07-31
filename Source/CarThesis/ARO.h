// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AROTarget.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARO.generated.h"

UCLASS()
class CARTHESIS_API AARO : public AActor
{
	GENERATED_BODY()
	
public:	
	AARO();

protected:
	virtual void BeginPlay() override;
#pragma region Divison Constants
	float forceDivision;
	float maxDistDivision;
#pragma endregion
#pragma region ARO Arrays
	TArray<FVector> forceVectorDirection;
	TArray<FVector> forceVector;
	TArray<float> currentDistance;
	TArray<float> acceleration;
	TArray<UAROTarget*> targetAROComponent;
#pragma endregion
#pragma region ARO Functions
	void CalculateAcceleration(int obj);
	void CalculateDirection(int obj);
	void SendAccelerations(int obj);
	void SetFormulaConstants();
	void SetArraysSize();
	void SetTargetAROArray();
#pragma endregion

public:
	virtual void Tick(float DeltaTime) override;
#pragma region Comunication Functions
	void SetNew(float newMinDistance, float newMaxDistance, int newForce, bool newRepulsion, TArray<AActor*> newAffectedObjects);
	void AddAffectedObject(AActor* newObject);
	void RemoveAffectedObject(AActor* targetObject);
#pragma endregion
#pragma region User Variables
	//Distance at which force becomes strongest.
	UPROPERTY(EditAnywhere)
	float minDistance;
	//Distance at which force starts working.
	UPROPERTY(EditAnywhere)
	float maxDistance;
	//The maximum force.
	UPROPERTY(EditAnywhere)
	float force;
	//On if you want to push instead of pull.
	UPROPERTY(EditAnywhere)
	bool repulsion;
	//Objects that will be affected by this ARO. WARNING: Objects must have AROTarget component in them.
	UPROPERTY(EditAnywhere)
	TArray<AActor*> affectedObjects;
#pragma endregion
};

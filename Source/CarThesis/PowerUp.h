// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARO.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UCLASS()
class CARTHESIS_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	APowerUp();

protected:
	virtual void BeginPlay() override;
	virtual void SetTargetAROs();
	virtual void SpawnARO(int AROHeader);
	virtual void FindTargets();
	void Destructor();
#pragma region Power Up Data
	UPROPERTY(EditAnywhere)
	float lifeTime;
	float lifeTimeLeft;
	UPROPERTY(EditAnywhere)
	AActor* throwerPlayer;
	TArray<AARO*> powerUpARO;
#pragma endregion
#pragma region ARO Data
	UPROPERTY(EditAnywhere)
	TSubclassOf<AARO> AROSpawn;
	UPROPERTY(EditAnywhere)
	float AROMinDistance;
	UPROPERTY(EditAnywhere)
	float AROMaxDistance;
	UPROPERTY(EditAnywhere)
	float AROForce;
	UPROPERTY(EditAnywhere)
	bool ARORepulsion;
	TArray<AActor*> AROAffectedObjects;
#pragma endregion

public:
	virtual void Tick(float DeltaTime) override;
	void SetThrowerPlayer(AActor* throwerPlayer);
};

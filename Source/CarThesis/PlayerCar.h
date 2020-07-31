// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARO.h"
#include "PowerUp.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCar.generated.h"

UCLASS()
class CARTHESIS_API APlayerCar : public APawn
{
	GENERATED_BODY()

public:
	APlayerCar();

protected:
	virtual void BeginPlay() override;
#pragma region Player Functions
	void GetAROTargetComponent();
	void AceleratorAROManager();
	void BreakAROManager();
	void RotationManager();
	void Kill();
	void Respawn();
#pragma endregion
#pragma region Blueprint Functions
	UFUNCTION(BlueprintCallable, Category = "PlayerCarScripts")
		void Accelerate(float axisValue);
	UFUNCTION(BlueprintCallable, Category = "PlayerCarScripts")
		void CarBreak(float axisValue);
	UFUNCTION(BlueprintCallable, Category = "PlayerCarScripts")
		void Right(float axisValue);
	UFUNCTION(BlueprintCallable, Category = "PlayerCarScripts")
		void Up(float axisValue);
	UFUNCTION(BlueprintCallable, Category = "PlayerCarScripts")
		void Rotate(float axisValue);
	UFUNCTION(BlueprintCallable, Category = "PlayerCarScripts")
		void AfterCrashVelocity(FVector collisionNormal);
	UFUNCTION(BlueprintCallable, Category = "PlayerCarScripts")
		void SpawnPowerUp();
	UFUNCTION(BlueprintCallable, Category = "PlayerCarScripts")
		void SetCheckpoint(FVector position, FRotator rotation);
#pragma endregion
#pragma region User Variables
	UPROPERTY(EditAnywhere)
		float rotateSpeed;
	UPROPERTY(EditAnywhere)
		float breakForce;
	UPROPERTY(EditAnywhere)
		AARO* breakARO;
	UPROPERTY(EditAnywhere)
		AARO* acceleratorARO;
#pragma endregion
#pragma region Player Variables
	UPROPERTY(VisibleAnywhere)
	int playerLife;
	float respawnTime;
	bool alive;
	FVector respawnPos;
	FRotator respawnRot;
	FVector acceleratorAROLocation;
	FVector breakAROLocation;
	FVector breakForceVector;
	FRotator lookAt;
	FTransform playerTransform;
	UAROTarget* myAROTargetComponent;
	TSubclassOf<APowerUp> powerUp;
#pragma endregion

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AddPowerUp(TSubclassOf<APowerUp> newPowerUp);
};

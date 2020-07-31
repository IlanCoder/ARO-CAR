// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerUp.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpBox.generated.h"

UCLASS()
class CARTHESIS_API APowerUpBox : public AActor
{
	GENERATED_BODY()
	
public:	
	APowerUpBox();

protected:
	virtual void BeginPlay() override;
	void Disappear();
	void Appear();
	UFUNCTION(BlueprintCallable, Category = "PowerUpBoxScripts")
	void OnCollision(AActor* collidingActor);
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APowerUp>> powerUpList;
	float disabledTime;
public:	
	virtual void Tick(float DeltaTime) override;
};
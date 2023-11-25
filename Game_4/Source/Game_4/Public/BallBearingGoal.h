// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "BallBearing.h"
#include "BallBearingGoal.generated.h"

/**
 * 
 */
UCLASS()
class GAME_4_API ABallBearingGoal : public ATriggerSphere
{
	GENERATED_BODY()

public:
	ABallBearingGoal();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Goal)
		float Magnetism = 7500.f;

	bool HasBallBearing() const;

protected:
	virtual void PostInitializeComponents() override;
	virtual void Tick(float deltaSeconds) override;
	virtual	void NotifyActorBeginOverlap(AActor* otherActor) override;
	virtual void NotifyActorEndOverlap(AActor* otherActor) override;
	

private:

	UPROPERTY(Transient)
		TArray< ABallBearing* > BallBearings;
	
};
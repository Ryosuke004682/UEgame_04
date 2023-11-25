// Fill out your copyright notice in the Description page of Project Setting

#include "BallBearingGoal.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"


ABallBearingGoal::ABallBearingGoal()
{
	SetActorHiddenInGame(false);
	PrimaryActorTick.bCanEverTick = true;
}

static float GetRatio(float value, float minimum, float maximum, bool clamp = true)
{
	if (value > maximum && clamp == true)
	{
		return 1.0f;
	}
	else if (value > minimum)
	{
		return (value - minimum) / (maximum - minimum);
	}
	else
	{
		return 0.f;
	}
}


void ABallBearingGoal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCollisionComponent()->SetHiddenInGame(true);


#if WITH_EDITORONLY_DATA
	GetSpriteComponent()->SetHiddenInGame(true);
#endif

}

void ABallBearingGoal::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	FVector ourLocation = GetActorLocation();
	float sphereRadius  = Cast<USphereComponent>(GetCollisionComponent())->GetScaledSphereRadius();
	float magnetism		= Magnetism;


	for (ABallBearing* ballBearing : BallBearings)
	{
		FVector difference = ourLocation - ballBearing->GetActorLocation();
		float distance = difference.Size();
		FVector direction = difference;

		direction.Normalize();

		float ratio = GetRatio(distance, 0.0f , sphereRadius);
		FVector force = (1.0f - ratio) * magnetism * direction;

		ballBearing->BallMesh->AddForce(force);
	}

}


void ABallBearingGoal::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);
	ABallBearing* BallBearing = Cast<ABallBearing>(otherActor);

	if (BallBearing != nullptr && BallBearing->Magnetized == true)
	{
		BallBearings.AddUnique(BallBearing);
	}
}

void ABallBearingGoal::NotifyActorEndOverlap(AActor* otherActor)
{
	Super::NotifyActorEndOverlap(otherActor);
	ABallBearing* BallBearing = Cast<ABallBearing>(otherActor);

	if (BallBearing != nullptr && BallBearing->Magnetized == true)
	{
		BallBearings.Remove(BallBearing);
	}
}


bool ABallBearingGoal::HasBallBearing() const
{
	FVector outLocation = GetActorLocation();

	for (const ABallBearing* ballBearing : BallBearings)
	{
		FVector difference = outLocation - ballBearing->GetActorLocation();
		float distance = difference.Size();


		if (distance < 75.f)
		{
			return true;
		}

		return false;
	}
}
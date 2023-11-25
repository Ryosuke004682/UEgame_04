// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "BallBearing.generated.h"

UCLASS()
class GAME_4_API ABallBearing : public APawn
{
	GENERATED_BODY()

public:
	ABallBearing();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BallBearing)
		UStaticMeshComponent* BallMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
		bool Magnetized = true;


	UFUNCTION(BlueprintCallable , Category = "Ball Bearing")
		void ResetLocation() const
	{
		BallMesh->SetWorldLocation(InitialLocation + FVector(0.f, 0.f, 150.f));
		BallMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		BallMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}




protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
	{
		Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal , NormalImpulse, Hit);

		InContact = true;
	}

	bool InContact = false;


private:
	FVector InitialLocation = FVector::ZeroVector;

	friend class ABallBearingHUD;
};

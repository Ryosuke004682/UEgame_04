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

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BallBearing)
		UStaticMeshComponent* BallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
		float Magnetized = 1.f;


protected:
	virtual void BeginPlay() override;
};

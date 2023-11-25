// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BallBearing.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerBallBearing.generated.h"

/**
 * 
 */
UCLASS()
class GAME_4_API APlayerBallBearing : public ABallBearing
{
	GENERATED_BODY()

	
	
public:
	
	APlayerBallBearing();

	/*Components*/
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = BallBearing)
		USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BallBearing)
		UCameraComponent* Camera = nullptr;
	
	/*Properties*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
		float ControllerForce = 250.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
		float JumpForce = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
		float DashForce = 150.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BallBearing)
		float MaximumSpeed = 4.f;

protected:

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	void MoveLongitudinally(float value) { InputLongitude = value; }
	void MoveLaterally(float value)	  { InputLatitude = value; }
	void Jump();
	void Dash();


	float InputLongitude = 0.0f;
	float InputLatitude  = 0.0f;
	float DashTimer		 = 0.0f;

	friend class ABallBearingHUD;
	

};

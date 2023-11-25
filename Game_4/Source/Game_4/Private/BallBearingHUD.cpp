// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBearingHUD.h"
#include "PlayerBallBearing.h"


void ABallBearingHUD::DrawHUD()
{
	Super::DrawHUD();

	APlayerBallBearing* BallBearing = Cast<APlayerBallBearing>(GetOwningPawn());

	if (BallBearing != nullptr)
	{
		AddFloat(L"Speed : " , BallBearing->GetVelocity().Size() / 10.f);
		AddFloat(L"Dash Timer : ", BallBearing-> DashTimer);
		AddFloat(L"Input latitude" , BallBearing->InputLatitude);
		AddFloat(L"Input longitude" , BallBearing->InputLongitude);
	}

}


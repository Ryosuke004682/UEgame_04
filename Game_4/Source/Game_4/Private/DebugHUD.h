// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "CanvasItem.h"
#include "DebugHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADebugHUD : public AHUD
{
	GENERATED_BODY()

public:


protected:
	ADebugHUD();

	void AddText(const TCHAR* title, const FText& value)
	{
		RenderStatistic(title, value);
	}

	void AddFloat(const TCHAR* title, float value)
	{
		RenderStatistic(title, FText::AsNumber(value));
	}

	void AddInt(const TCHAR* title, int32 value)
	{
		RenderStatistic(title, FText::AsNumber(value));
	}

	void AddBool(const TCHAR* title, bool value)
	{
		RenderStatistic(title , BoolToText(value) , (value == false) ? FLinearColor::Red : FLinearColor::Green);
	}

	virtual void DrawHUD() override
	{
		X = Y = 50.f;
	}

	float HorizontalOffset = 150.f;

private:

	//StringŒ^‚ðTextŒ^‚É•ÏŠ·
	FText CStringToText(const TCHAR* text)
	{
		return FText::FromString(text);
	}
	
	//BoolŒ^‚ðTextŒ^‚É•ÏŠ·
	FText BoolToText(bool value)
	{
		return CStringToText((value == true) ? TEXT("true") : TEXT("false"));
	}


	void RenderStatistic(const TCHAR* title , const FText& value , const FLinearColor& valueColor = FLinearColor::White)
	{
		FCanvasTextItem item0(FVector2D(X , Y) , CStringToText(title) , MainFont, FLinearColor::White);
		item0.EnableShadow(FLinearColor(0.f , 0.f , 0.f));
		Canvas->DrawItem(item0);
		
		FCanvasTextItem item1(FVector2D(X + HorizontalOffset , Y) , value , MainFont , valueColor);
		Canvas->DrawItem(item1);
		Y += LinerHeight;

	}

	UPROPERTY(Transient)
		UFont* MainFont = nullptr;


	float X = 50.f;
	float Y = 50.f;

	float LinerHeight = 16.f;



};

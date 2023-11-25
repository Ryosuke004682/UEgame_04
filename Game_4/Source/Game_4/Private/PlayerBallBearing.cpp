// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBallBearing.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"

APlayerBallBearing::APlayerBallBearing()
{
	/*SpringArmComponent*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-45.f , 0.f , 0.f));
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(BallMesh);

	/*CameraComponent*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm , USpringArmComponent::SocketName);

	Magnetized = false;
}


/// <summary>
/// ì¸óÕÇÃê›íË
/// </summary>
static void InitializeDefaultPawnInputBindings()
{
	static bool bindingsAdded = false;

	if (bindingsAdded == false)
	{
		bindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::W ,  1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::S,  -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Up,  1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Down, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLongitudinally", EKeys::Gamepad_DPad_Left, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::D,  1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Left, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Right, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("BallBearing_MoveLaterally", EKeys::Gamepad_DPad_Right, -1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("BallBearing_Jump", EKeys::Enter));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("BallBearing_Dash", EKeys::SpaceBar));
	}
}

void APlayerBallBearing::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	check(playerInputComponent != nullptr);

	Super::SetupPlayerInputComponent(playerInputComponent);

	InitializeDefaultPawnInputBindings();

	playerInputComponent->BindAxis("BallBearing_MoveLongitudinally" , this , &APlayerBallBearing::MoveLongitudinally);
	playerInputComponent->BindAxis("BallBearing_MoveLaterally", this , &APlayerBallBearing::MoveLaterally);

	playerInputComponent->BindAction("BallBearing_Jump", EInputEvent::IE_Pressed, this, &APlayerBallBearing::Jump);
	playerInputComponent->BindAction("BallBearing_Dash", EInputEvent::IE_Pressed, this, &APlayerBallBearing::Dash);
}

void APlayerBallBearing::Jump()
{
	if (InContact == true)
	{
		BallMesh->AddImpulse(FVector(0.f, 0.f, JumpForce * 1000.f));
	}
}

void APlayerBallBearing::Dash()
{
	if (DashTimer == 0.f)
	{
		FVector velocity = BallMesh->GetPhysicsLinearVelocity();

		if (velocity.Size() > 1.f)
		{
			velocity.Normalize();
			velocity *= DashForce * 1000.f;
			BallMesh->AddImpulse(velocity);
			DashTimer = 1.5f;
		}
	}
}

void APlayerBallBearing::MyTestFunction(const TArray<float>& inParam1, UPARAM(ref)TArray<float>& inParam2, TArray<float>& outParam1, const AActor* inParam3, UPARAM(ref)AActor* inParam4, AActor* inParam5, AActor*& outParam2, const int32 inParam6, UPARAM(ref)int32 inParam7, int32 inParam8, const int32& inParam9, int32& outParam3)
{
}


void APlayerBallBearing::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	FVector velocity = BallMesh->GetPhysicsLinearVelocity();
	float z = velocity.Z;

	velocity.Z = 0.f;


	if (velocity.Size() > MaximumSpeed * 100.f)
	{
		velocity.Normalize();
		velocity *= MaximumSpeed * 100.f;
		velocity.Z = z;

		UE_LOG(LogTemp, Warning, TEXT("ïœêîÇÃíl: %f"), velocity.Z);

		float brakingRadio = FMath::Pow(1.f - FMath::Min(DashTimer , 1.f) , 2.f);
		FVector mergedVelocity = FMath::Lerp(BallMesh->GetPhysicsLinearVelocity() , velocity , brakingRadio);

		BallMesh->SetPhysicsLinearVelocity(mergedVelocity);
	}
	else
	{
		BallMesh->AddForce(FVector(InputLongitude, InputLatitude, 0.f) * ControllerForce * BallMesh->GetMass());
	}

	if (DashTimer > 0.f)
	{
		DashTimer = FMath::Max(0.f , DashTimer - deltaTime);
	}
}
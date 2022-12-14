// Copyright Epic Games, Inc. All Rights Reserved.

#include "UNREALTASK6Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/SkeletalMeshSocket.h"


//////////////////////////////////////////////////////////////////////////
// AUNREALTASK6Character

AUNREALTASK6Character::AUNREALTASK6Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//WEAPON STUFF
	weaponIndex = 0;
	isHoldingPistol = false;
	
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUNREALTASK6Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//SETING UP SWITCH FUNCTION
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AUNREALTASK6Character::SwitchWeapon);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AUNREALTASK6Character::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AUNREALTASK6Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AUNREALTASK6Character::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AUNREALTASK6Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUNREALTASK6Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUNREALTASK6Character::TouchStopped);
}

void AUNREALTASK6Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AUNREALTASK6Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AUNREALTASK6Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AUNREALTASK6Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AUNREALTASK6Character::WeaponAdd(AWeapon* weapon)
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Added"));
	IntArray.Push(weapon);
}

void AUNREALTASK6Character::EquipWeapon(AWeapon* weaponFloor)
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Equipped"));
}

void AUNREALTASK6Character::SwitchWeaponMesh(int currentIndex)
{
	
}

void AUNREALTASK6Character::SwitchWeapon()
{

	//GetAttachedActors(IntArray, true, true);
	/*for (auto& Actor : IntArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("AllWeapons: %s"), *Actor->GetName())
	}*/
	//int numbInArray;
	//numbInArray = IntArray.Num();
	//UE_LOG(LogTemp, Warning, TEXT("AllWeapons: %s"), numbInArray);
	//USkeletalMeshSocket* PlayerMesh = GetSocketByName("hand_rSocket_rifle");
	switch (weaponIndex)
	{
		case 0:
			if (IntArray.Num() > 0) {
				weaponIndex = 1;
				//switch mesh
				UE_LOG(LogTemp, Warning, TEXT("Weapon 1"));
				SwitchWeaponMesh(weaponIndex);
				//EquippedWeapon = IntArray[weaponIndex];
				//UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), EquippedWeapon);
			}
		/*	else
			{
				weaponIndex = 0;
			}*/
			break;
		case 1:
			if (IntArray.Num() > 1) {
				weaponIndex = 0;
				//switch mesh
				UE_LOG(LogTemp, Warning, TEXT("Weapon 2"));
				SwitchWeaponMesh(weaponIndex);
			}
		/*	else
			{
				weaponIndex = 0;
			}*/
			break;
		default:
			break;
	}
	
}


void AUNREALTASK6Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUNREALTASK6Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

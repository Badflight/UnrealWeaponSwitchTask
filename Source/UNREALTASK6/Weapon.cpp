// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "UNREALTASK6Character.h"
#include "Engine/SkeletalMeshSocket.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Volume"));
	RootComponent = CollisionVolume;
	SkeletalMesh = CreateAbstractDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	bIsGun = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnOverlapEnd);

}

void AWeapon::Equip(AUNREALTASK6Character* Char) {
	if (Char) {
		//USkeletalMeshSocket* Socket;
		if (bIsGun) {
			const USkeletalMeshSocket* Socket = Char->GetMesh()->GetSocketByName("hand_rSocket_rifle");
			if (Socket) {
				Socket->AttachActor(this, Char->GetMesh());
				Char->SetEquippedWeapon(this);
			}
		}
		else {
			const USkeletalMeshSocket* Socket = Char->GetMesh()->GetSocketByName("hand_rSocket_pistol");
			if (Socket) {
				Socket->AttachActor(this, Char->GetMesh());
				Char->SetEquippedWeapon(this);
			}
		}
	}
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) {
		AUNREALTASK6Character* Char = Cast<AUNREALTASK6Character>(OtherActor);
		if (Char) {
			Equip(Char);
		}
}
}
void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

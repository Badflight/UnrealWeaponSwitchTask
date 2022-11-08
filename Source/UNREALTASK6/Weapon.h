// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UNREALTASK6Character.h"
#include "Components/SphereComponent.h"
#include "Weapon.generated.h"

UCLASS()
class UNREALTASK6_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Skeletal Mesh")
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Collision Volume")
		USphereComponent* CollisionVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Equip(class AUNREALTASK6Character* Char);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Properties")
	bool bIsGun;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

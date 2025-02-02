// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"



// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankTurret;
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	virtual void TickComponent(float DelatTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector AimDirection);

	void MoveTurret(FVector AimDirection);

	FVector AimDirection = FVector(0.f,0.f,0.f);

	bool IsBarrelMoving() const;

	

	

	float LastFireTime = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

	UPROPERTY(BlueprintReadOnly, EditAnywhere ,Category = "State")
	int32 ShotsLeft = 3;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ReloadTimeInSeconds = 3.f;

public:	

	UTankBarrel* Barrel;
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Fire();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 8000.f; // Sensible starting value

	EFiringState GetFiringState();
};

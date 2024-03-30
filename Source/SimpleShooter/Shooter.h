// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shooter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPresent() const;

	UFUNCTION(BlueprintPure)
	bool GetIsShooting() const;


private:
    void MoveForward(float Value);

	void MoveLeftRight(float Value);

	void LookUpRate(float Value);

	void LookLeftRightRate(float Value);

	
	
	
	

	UPROPERTY(EditAnywhere)
	float RotationRate;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;


	FTimerHandle CooldownHandle;

	float CoolDown = 0.70;

	bool bCanShoot;

	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY()
	bool bIsShooting = false;

	void DelayControl();

};

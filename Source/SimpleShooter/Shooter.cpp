// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	Health = MaxHealth;
	bCanShoot = true;
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &AShooter::MoveLeftRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooter::Shoot);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRightRate"), this, &AShooter::LookLeftRightRate);
	

}

void AShooter::MoveForward(float Value){
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShooter::MoveLeftRight(float Value){
	AddMovementInput(GetActorRightVector() * Value);
}

void AShooter::LookUpRate(float Value){
	AddControllerPitchInput(RotationRate * Value * GetWorld()->GetDeltaSeconds());
}

void AShooter::LookLeftRightRate(float Value){
	AddControllerYawInput(RotationRate * Value * GetWorld()->GetDeltaSeconds());
}

void AShooter::Shoot(){
	if(bCanShoot){
		bCanShoot = false;
		Gun->PullTrigger();
	    bIsShooting = true;
		GetWorldTimerManager().SetTimer(CooldownHandle, this, &AShooter::DelayControl, CoolDown, false);
	}	
}



void AShooter::DelayControl(){
	bCanShoot = true;
	bIsShooting = false;
}

bool AShooter::GetIsShooting() const{
	return bIsShooting;
}

float AShooter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	float AppliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	AppliedDamage = FMath::Min(Health, AppliedDamage);
	Health -= AppliedDamage;
	if(IsDead()){
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(GameMode){
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		
	}
	return AppliedDamage;
}

bool AShooter::IsDead() const{
	return Health <= 0;
}

float AShooter::GetHealthPresent() const
{
    return Health/MaxHealth;
}


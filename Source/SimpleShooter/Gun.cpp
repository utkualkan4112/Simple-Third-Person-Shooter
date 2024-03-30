// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult &Hit, FVector &ShotDirection)
{
    
	AController* PawnController = GetOwnerController();
	if(PawnController == nullptr){
		return false;
	}
	FVector Location;
	FRotator Rotation;
	PawnController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner()); 
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController *AGun::GetOwnerController() const
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr){
		return nullptr;
	} 
	return OwnerPawn->GetController();
}

void AGun::PullTrigger(){
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));
	FHitResult HitResult;
	FVector ShotDirection;
	bool bSuccess = GunTrace(HitResult, ShotDirection);
	if(bSuccess){
		UGameplayStatics::SpawnEmitterAtLocation(this, Impact, HitResult.ImpactPoint, ShotDirection.Rotation(), true);
		UGameplayStatics::SpawnSoundAtLocation(this, ImpactSound, HitResult.ImpactPoint, ShotDirection.Rotation(), true);	
		AActor* HitActor = HitResult.GetActor();
		if(HitActor){
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController* PawnController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, PawnController, this);
		}
	}
	
}


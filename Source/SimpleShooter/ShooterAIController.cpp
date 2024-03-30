// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Shooter.h"

void AShooterAIController::BeginPlay(){
    Super::BeginPlay();
     if(AIBehavior){
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooter* ControlledChracter = Cast<AShooter>(GetPawn());
    if(ControlledChracter){
        return ControlledChracter->IsDead();
    }
    return true;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode_Shoot.h"
#include "AIController.h"
#include "Shooter.h"

UMyBTTaskNode_Shoot::UMyBTTaskNode_Shoot(){
    NodeName = TEXT("Shoot");
}


EBTNodeResult::Type UMyBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if(OwnerComp.GetAIOwner() == nullptr){
        return EBTNodeResult::Failed;
    }

    AShooter* Shooter = Cast<AShooter>(OwnerComp.GetAIOwner()->GetPawn());
    if(Shooter == nullptr){
        return EBTNodeResult::Failed;
    }
    Shooter->Shoot();
    return EBTNodeResult::Succeeded;
}


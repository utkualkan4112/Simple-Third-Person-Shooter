// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocatioIfSee.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTService_PlayerLocatioIfSee::UBTService_PlayerLocatioIfSee(){
    NodeName = TEXT("Update Player Location If See");
}

void UBTService_PlayerLocatioIfSee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(Player){
        if(OwnerComp.GetAIOwner()){
            AAIController* AIController = OwnerComp.GetAIOwner();
            if(AIController->LineOfSightTo(Player)){
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Player);
            }
            else{
                OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
            }
        }

    }

}


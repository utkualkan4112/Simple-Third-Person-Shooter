// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Shooter.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner){
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if(bIsWinner){
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen){
            WinScreen->AddToViewport();
            HUD->RemoveFromParent();
        }
    }
    else{
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen){
            LoseScreen->AddToViewport();
            HUD->RemoveFromParent();
        }
    }
    
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);


}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    HUD = CreateWidget(this, HUDClass);
    if(HUD){
        HUD->AddToViewport();
    }
    
    

}

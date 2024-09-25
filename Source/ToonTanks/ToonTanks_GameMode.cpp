// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "TT_PlayerController.h"


void AToonTanks_GameMode::BeginPlay()
{
	Super::BeginPlay();

	Handle_GameStart();
}





void AToonTanks_GameMode::Handle_GameStart()
{

	Target_Towers = Get_TowerCount();

	Tank_class = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	TT_PlyrController = Cast<ATT_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));


	Start_Game();


	if (TT_PlyrController)
	{
		TT_PlyrController->SetPlayer_enabledState(false);

		FTimerHandle plyr_Enable_TimerHandle;
		FTimerDelegate plyr_Enable_TimerDelegate = FTimerDelegate::CreateUObject(
			TT_PlyrController, &ATT_PlayerController::SetPlayer_enabledState, true);


		GetWorldTimerManager().SetTimer(plyr_Enable_TimerHandle, plyr_Enable_TimerDelegate,
			start_Delay, false);
	}
}









void AToonTanks_GameMode::Actor_Died(AActor* dead_Actor)
{
	if (dead_Actor == Tank_class)
	{
		Tank_class->Handle_Destruction();

		if (TT_PlyrController)
		{
			TT_PlyrController->SetPlayer_enabledState(false);

			//Tank_class->DisableInput(Tank_class->Get_TankPlyrContrl());
			//Tank_class->Get_TankPlyrContrl()->bShowMouseCursor = false;
		}
		GameOver(false);
	}

	else if (ATower* destroyed_Tower = Cast<ATower>(dead_Actor))
	{
		destroyed_Tower->Handle_Destruction();


		Target_Towers--;  //--Target_Towers da ayný iþlem


		if (Target_Towers == 0)
		{
			GameOver(true);
		}
	}
}






int32 AToonTanks_GameMode::Get_TowerCount()
{
	TArray<AActor*> Towers;

	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ToonTanks_GameMode.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API AToonTanks_GameMode : public AGameModeBase
{
	GENERATED_BODY()



public:
	void Actor_Died(AActor* dead_Actor);



protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void Start_Game();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool b_WonGame);


private:
	class ATank* Tank_class;
	class ATT_PlayerController* TT_PlyrController;

	UPROPERTY(EditAnywhere)
	float start_Delay;

	void Handle_GameStart();

	int32 Target_Towers;
	int32 Get_TowerCount();

};



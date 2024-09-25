// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pawn.h"
#include "Tower.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATower : public ABase_Pawn
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Handle_Destruction();

private:

	class ATank* Tank_class;
	FVector first_Vector;

	UPROPERTY(EditAnywhere, Category = "Tower")
	float Fire_Range;
	UPROPERTY(EditAnywhere, Category = "Tower")
	float Fire_Rate;

	FTimerHandle fire_Rate_TimerHandle;
	void Check_Fire();

	bool In_FireRange();


	//void Debug_Line_();

};

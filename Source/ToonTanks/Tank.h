
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Pawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABase_Pawn
{
	GENERATED_BODY()

	ATank();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Handle_Destruction();



public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* Get_TankPlyrContrl() const { return Tank_PlyrController; }

	bool IsAlive = true;



private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Comps")
	class USpringArmComponent* Spring_Arm;

	UPROPERTY(VisibleDefaultsOnly, Category = "Comps")
	class UCameraComponent* Camera_;

	UPROPERTY(EditAnywhere, Category = "Move")
	float Move_Speed;
	UPROPERTY(EditAnywhere, Category = "Move")
	float Turn_Speed;



	void Move(float Value);
	void Turn(float Value);


	APlayerController* Tank_PlyrController;




};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



private:

	UPROPERTY(EditAnywhere)
	float Max_Health = 100;
	UPROPERTY(VisibleAnywhere)
	float curr_Health;

	UFUNCTION()
	void Damage_Taken(
		AActor* Damaged_Actor, float Damage, const UDamageType* Damage_type,
		class AController* Instigator, AActor* DamageCauser);




	class AToonTanks_GameMode* TT_GameMode;






};

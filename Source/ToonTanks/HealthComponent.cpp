// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks_GameMode.h"
#include "Base_Pawn.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	curr_Health = Max_Health;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::Damage_Taken);

	TT_GameMode = Cast<AToonTanks_GameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//
}











void UHealthComponent::Damage_Taken(AActor* Damaged_Actor, float Damage,
	const UDamageType* Damage_type, class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0 && curr_Health <= 0) return;

	curr_Health -= Damage;

	//UE_LOG(LogTemp, Warning, TEXT("%s Health: %f"), *Damaged_Actor->GetName(), curr_Health);


	if (curr_Health <= 0 && TT_GameMode)
	{
		Cast<ABase_Pawn>(GetOwner())->Explode();

		TT_GameMode->Actor_Died(Damaged_Actor);
	}
}


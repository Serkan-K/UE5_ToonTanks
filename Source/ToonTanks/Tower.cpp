// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"



// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank_class = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	first_Vector = ABase_Pawn::Turret_reset();


	GetWorldTimerManager().SetTimer(fire_Rate_TimerHandle, this, &ATower::Check_Fire, Fire_Rate, true);


}



void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (In_FireRange())
	{
		Rotate_(Tank_class->GetActorLocation());
	}
	else
	{
		Rotate_(GetActorLocation() + first_Vector);
	}


	//Debug_Line_();

	//if (Tank_class)
	//{
	//	float Distance_ = FVector::Dist(GetActorLocation(), Tank_class->GetActorLocation());
	//	if (Distance_ <= Fire_Range)
	//	{
	//		Rotate_(Tank_class->GetActorLocation());
	//	}
	//	else
	//	{
	//		Rotate_(GetActorLocation() + first_Vector);
	//	}
	//}
}












void ATower::Handle_Destruction()
{
	Super::Handle_Destruction();
	Destroy();
}












void ATower::Check_Fire()
{
	if (Tank_class == nullptr) return;

	if (In_FireRange() && Tank_class->IsAlive)
	{
		Fire();
	}
}


bool ATower::In_FireRange()
{
	if (Tank_class)
	{
		float Distance_ = FVector::Dist(GetActorLocation(), Tank_class->GetActorLocation());

		if (Distance_ <= Fire_Range)
		{
			return true;
		}
	}
	return false;
}








//
//void ATower::Debug_Line_()
//{
//
//	FVector start_Point = GetActorLocation();
//	FVector Tank_Pos = Tank_class->GetActorLocation();
//
//	float Distance_ = FVector::Dist(GetActorLocation(), Tank_Pos);
//	float Line_Length = FMath::Min(Distance_, Fire_Range);
//
//	FVector direction = (Tank_Pos - start_Point).GetSafeNormal();
//	FVector end_Point = start_Point + (direction * Line_Length);
//
//
//
//
//	if (Distance_ <= Line_Length)
//		DrawDebugLine(GetWorld(), start_Point, end_Point, FColor::Red, false, .1);
//	else
//	{
//		DrawDebugLine(GetWorld(), start_Point, end_Point, FColor::Green, false, .1);
//	}
//
//
//}
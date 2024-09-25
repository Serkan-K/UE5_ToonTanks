// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"



ATank::ATank()
{
	Spring_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Spring_Arm->SetupAttachment(RootComponent);

	Camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera_->SetupAttachment(Spring_Arm);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	Tank_PlyrController = Cast<APlayerController>(GetController());

}




// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank_PlyrController)
	{
		FHitResult hit_Res;
		Tank_PlyrController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit_Res);

		//DrawDebugSphere(GetWorld(), hit_Res.ImpactPoint, 10, 2, FColor::Emerald, false, -1);

		Rotate_(hit_Res.ImpactPoint);
	}
}



void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}













void ATank::Handle_Destruction()
{
	Super::Handle_Destruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	IsAlive = false;
}









void ATank::Move(float Value_)
{
	FVector delta_Loc = FVector::ZeroVector;
	delta_Loc.X = Value_ * Move_Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(delta_Loc, true);
	//UE_LOG(LogTemp, Display, TEXT("move ileri %s"), *delta_Loc.ToString());
}


void ATank::Turn(float _Value)
{
	FRotator delta_turn = FRotator::ZeroRotator;
	delta_turn.Yaw = _Value * Turn_Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(delta_turn, true);
	//UE_LOG(LogTemp, Display, TEXT("move yan %s"), *delta_turn.ToString());
}
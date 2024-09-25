// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABase_Pawn::ABase_Pawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Capsule_comp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = Capsule_comp;

	Base_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	Base_mesh->SetupAttachment(Capsule_comp);

	Turret_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	Turret_mesh->SetupAttachment(Base_mesh);

	Projectile_SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	Projectile_SpawnPoint->SetupAttachment(Turret_mesh);


}










void ABase_Pawn::Rotate_(FVector Look_Target)
{
	FVector to_Target = Look_Target - Turret_mesh->GetComponentLocation();
	FRotator look_Rotation = FRotator(0, to_Target.Rotation().Yaw, 0);

	Turret_mesh->SetWorldRotation(
		FMath::RInterpTo(
			Turret_mesh->GetComponentRotation(),
			look_Rotation,
			GetWorld()->DeltaTimeSeconds, 5));
}













void ABase_Pawn::Fire()
{
	//DrawDebugSphere(GetWorld(), projectile_SpawnPoint, 5, 1, FColor::Red, false, 1);

	FVector prjctl_Loc = Projectile_SpawnPoint->GetComponentLocation();
	FRotator prjctl_Rot = Projectile_SpawnPoint->GetComponentRotation();

	AProjectile* Projctl = GetWorld()->SpawnActor<AProjectile>(Projectile_Class, prjctl_Loc, prjctl_Rot);
	Projctl->SetOwner(this);
}




void ABase_Pawn::Handle_Destruction()
{
	if (death_Particles)
		UGameplayStatics::SpawnEmitterAtLocation(this, death_Particles, GetActorLocation(), GetActorRotation());

	if (death_SFX)
		UGameplayStatics::PlaySoundAtLocation(this, death_SFX, GetActorLocation());
	if(die_CamShake_Class)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(die_CamShake_Class);
}














void ABase_Pawn::Explode()
{
	IsDead = true;


	TInlineComponentArray<UPrimitiveComponent*> Components(this);
	for (UPrimitiveComponent* Comp : Components)
	{
		Comp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		Comp->SetSimulatePhysics(true);
	}

	FVector RandomDirection = FVector(FMath::FRandRange(-1.f, 1.f),
		FMath::FRandRange(-1.f, 1.f), FMath::FRandRange(0.f, 1.f)).GetSafeNormal();


	SetLifeSpan(3);
}










FVector ABase_Pawn::Turret_reset()
{
	return Turret_mesh->GetForwardVector();
}



// Called to bind functionality to input
//void ABase_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}


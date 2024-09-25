// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Projectile_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = Projectile_mesh;

	Projectile_moveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	Projectile_moveComp->MaxSpeed = 1500;
	Projectile_moveComp->InitialSpeed = 500;


	trails_Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke trail"));
	trails_Particles->SetupAttachment(RootComponent);
}




// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Projectile_mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);


	if (fire_SFX)
		UGameplayStatics::PlaySoundAtLocation(this, fire_SFX, GetActorLocation(), 2);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

















void AProjectile::OnHit(UPrimitiveComponent* hit_Comp, AActor* other_Actor,
	UPrimitiveComponent* other_Comp, FVector normal_Impulse, const FHitResult& hit)
{

	AActor* my_Owner = GetOwner();
	if (my_Owner == nullptr)
	{
		Destroy();
		return;
	}

	AController* my_OwnerInstigator = my_Owner->GetInstigatorController(); //auto = var gibimsi
	UClass* my_DmgTypeClass = UDamageType::StaticClass();

	if (other_Actor && other_Actor != this && other_Actor != my_Owner)
	{
		UGameplayStatics::ApplyDamage(other_Actor, Damage_, my_OwnerInstigator, this, my_DmgTypeClass);

		if (hit_Particles)
			UGameplayStatics::SpawnEmitterAtLocation(this, hit_Particles, GetActorLocation(), GetActorRotation());
		if (hit_SFX)
			UGameplayStatics::PlaySoundAtLocation(this, hit_SFX, GetActorLocation(), .5, 
				UKismetMathLibrary::RandomFloatInRange(.5, 2));
		if (hit_CamShake_Class)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hit_CamShake_Class);
	}

	Destroy();



	//UE_LOG(LogTemp, Warning, TEXT("OnHit")); vurdu
	//UE_LOG(LogTemp, Display, TEXT("HitComp: %s"), *hit_Comp->GetName()); projectile
	//UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *other_Actor->GetName()); vurulan
}

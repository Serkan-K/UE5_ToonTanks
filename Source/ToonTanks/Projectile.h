// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

class USoundBase;


UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



private:


	UPROPERTY(EditAnywhere)
	float Damage_;



	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Projectile_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Move")
	class UProjectileMovementComponent* Projectile_moveComp;



	UFUNCTION()
	void OnHit(UPrimitiveComponent* hit_Comp, AActor* other_Actor,
		UPrimitiveComponent* other_Comp, FVector normal_Impulse, const FHitResult& hit);





	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* hit_Particles;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* trails_Particles;



	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* fire_SFX;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* hit_SFX;


	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> hit_CamShake_Class;

};

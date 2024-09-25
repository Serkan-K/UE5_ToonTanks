// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Base_Pawn.generated.h"

UCLASS()
class TOONTANKS_API ABase_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABase_Pawn();

	void Handle_Destruction();

	void Explode();




protected:
	void Rotate_(FVector Look_Target);
	void Fire();

	FVector Turret_reset();


	bool IsDead;







private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components_", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* Capsule_comp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components_", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Base_mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components_", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Turret_mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components_", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Projectile_SpawnPoint;



	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> Projectile_Class;


	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* death_Particles;



	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* death_SFX;



	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> die_CamShake_Class;

	//public:
	//	// Called every frame
	//	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};

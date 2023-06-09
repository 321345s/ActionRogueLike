// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerupActor_HealthPotion.generated.h"

/**
 * 
 */
class UStaticMeshComponent;
class USoundCue;

UCLASS()
class ACTIONROGUELIKE_API ASPowerupActor_HealthPotion : public ASPowerupActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundCue* PowerupSound;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;
	ASPowerupActor_HealthPotion();
	
};

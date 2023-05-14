// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor_HealthPotion.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"


ASPowerupActor_HealthPotion::ASPowerupActor_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	PowerupSound = CreateDefaultSubobject<USoundCue>("PowerupSound");
}


void ASPowerupActor_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	UKismetSystemLibrary::PrintString(this, "Hello HealthPotion");
	if (!ensure(InstigatorPawn)) {
		return;
	}
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth()) {
		if (AttributeComp->ApplyHealthChange(AttributeComp->GetHealthMax())) {
			UGameplayStatics::SpawnSoundAttached(PowerupSound, GetRootComponent());
			HideAndCooldownPowerup();
		}
	}
}

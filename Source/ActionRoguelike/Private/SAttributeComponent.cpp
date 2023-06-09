// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include "SGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("FDU.DamageMultiplier"), 1.0f, TEXT("Global DamageMultiplier for Attribute component."), ECVF_Cheat);


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	HealthMax = 100;
	Health = HealthMax;
	LowHealth = 50;
	// ...
}



bool USAttributeComponent::IsAlive() const {
	return Health > 0.0f;
}


bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged()&&Delta<0.0f) {
		return false;
	}

	if (Delta < 0.0f) {
		Delta *= CVarDamageMultiplier.GetValueOnGameThread();
	}


	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	float ActualDelta = Health - OldHealth;
	onHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);


	//died
	if (ActualDelta < 0.0f && Health == 0.0f) {
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GM) {
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDelta != 0;
}

bool USAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor) {
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
		USAttributeComponent* AttributeComp = GetAttributes(Actor);
		if (AttributeComp) {
			return AttributeComp->IsAlive();
		}

	return false;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}

bool USAttributeComponent::IsLowHealth() const
{
	return Health <= LowHealth;
}




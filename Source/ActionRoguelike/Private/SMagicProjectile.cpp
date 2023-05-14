// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;


	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	damage = -20;

	//sound
	/*SoundLoop = CreateDefaultSubobject<USoundCue>("SoundLoop");
	SoundImpact = CreateDefaultSubobject<USoundCue>("SoundImpact");*/
	/*AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(SphereComp);
	AudioComp->SetSound(SoundLoop);*/

}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	/*UGameplayStatics::SpawnSoundAttached(SoundLoop,GetRootComponent());*/
	/*AudioComp = UGameplayStatics::SpawnSoundAttached(SoundLoop, GetRootComponent());*/
}

void ASMagicProjectile::OnActorOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor&& OtherActor!=GetInstigator()) {
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp) {
			AttributeComp->ApplyHealthChange(GetInstigator(),damage);
			/*AudioComp = UGameplayStatics::SpawnSoundAttached(SoundImpact, GetRootComponent());
			AudioComp->Stop();*/
			
			/*Destroy();*/
		}
	}
}

//void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//	if (OtherActor && OtherActor != GetInstigator()) {
//		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
//		if (AttributeComp) {
//			AttributeComp->ApplyHealthChange(damage);
//			/*AudioComp = UGameplayStatics::SpawnSoundAttached(SoundImpact, GetRootComponent());
//			AudioComp->Stop();*/
//
//			/*Destroy();*/
//		}
//	}
//
//}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


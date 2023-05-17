// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;
class USoundCue;
class USActorComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;

	//sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundCue* SoundDead;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundCue* SoundCastMagic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundCue* SoundBlackhole;



	UPROPERTY(EditAnywhere,Category="Attack")
		UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
		float AttackAnimDelay;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName HandSocketName;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Dash;
	FTimerHandle TimerHandle_BlackHole;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
		USInteractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USActorComponent* ActionComp;
	//audio
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* HammerSound;

	void MoveForward(float value);
	void MoveRight(float value);

	void PrimaryAttack();
	void PrimaryInteract();

	void PrimaryAttack_TimeElapsed();

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	void Dash();
	void Dash_TimeElapsed();

	void BlackHoleAttack();
	void BlackHoleAttack_TimeElapesed();

	void DashShift();
	void DashShiftComplete();

	void KillSelf();
	void RestartGame();
	void QuitGame();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION(Exec)
	void HealSelf(float Amout=100);

};

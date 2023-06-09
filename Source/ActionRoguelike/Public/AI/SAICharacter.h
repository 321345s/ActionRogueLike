// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;
class USAttributeComponent;
class AActor;
class UUserWidget;
class USWorldUserWidget;
class USoundCue;

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASAICharacter();

	UFUNCTION(BlueprintCallable)
		USWorldUserWidget* GetHealthBar();

	UFUNCTION(BlueprintCallable)
		void SetHealthBarNullptr();

	USoundCue* GetShotAudio();

protected:

	USWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	void SetTargetActor(AActor* NewTarget);

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundCue* SoundDied;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundCue* SoundShot;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USAttributeComponent* AttributeComp;
	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

};

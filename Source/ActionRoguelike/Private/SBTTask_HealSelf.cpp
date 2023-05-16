// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTTask_HealSelf.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type USBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController)) {
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr) {
			return EBTNodeResult::Failed;
		}
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(MyPawn->GetComponentByClass(USAttributeComponent::StaticClass()));


		return (AttributeComp->ApplyHealthChange(MyPawn, AttributeComp->GetHealthMax())) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;

	}

	return EBTNodeResult::Failed;
}

USBTTask_HealSelf::USBTTask_HealSelf()
{
	
}

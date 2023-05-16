// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_CheckLowHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SAttributeComponent.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackBoardComp)) {

		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController)) {
			APawn* AIPawn = MyController->GetPawn();
			if (ensure(AIPawn)) {
				USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
				BlackBoardComp->SetValueAsBool(IsLowHealth.SelectedKeyName, AttributeComp->IsLowHealth());
			}
		}
	}
}

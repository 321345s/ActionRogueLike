// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SPlayerState.h"
#include "AI/SAICharacter.h"
#include "SWorldUserWidget.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp)) {
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
		if (TargetActor) {
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController)) {
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn)) {
					float distanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
					bool bWithinRange = distanceTo < 2000.0f;
					bool bHasLOS = false;
					if (bWithinRange) {
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}

					if (!bHasLOS) {
						ASAICharacter* AICharacter = Cast<ASAICharacter>(AIPawn);
						if (AICharacter) {
							USWorldUserWidget* HealthBar = AICharacter->GetHealthBar();
							if (HealthBar) {
								HealthBar->RemoveFromParent();
								AICharacter->SetHealthBarNullptr();
							}
							
						}
						
					}

					

					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bHasLOS&&bWithinRange));
				}
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "FGPlayertController.h"

#include "FGCharacter.h"

void AFGPlayertController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AFGPlayertController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AFGPlayertController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	AFGCharacter* C = Cast<AFGCharacter>(P);
	if (C)
	{
		C->GetAbilitySystemComponent()->InitAbilityActorInfo(C, C);
		
	}
}

void AFGPlayertController::BeginPlay()
{
	Super::BeginPlay();
}

void AFGPlayertController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFGPlayertController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGPlayertController.generated.h"

/**
 * 
 */
UCLASS()
class FASTGAS_API AFGPlayertController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* aPawn)override;
	virtual void OnUnPossess()override;
	virtual void AcknowledgePossession(class APawn* P)override;
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void SetupInputComponent()override;
};

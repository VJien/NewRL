// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FastGas/Data/FGTargetType.h"
#include "FastGas/Core/FGCharacter.h"
#include "RLCharacter.generated.h"

UCLASS()
class SCIFI_RL_API ARLCharacter : public AFGCharacter
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's properties

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

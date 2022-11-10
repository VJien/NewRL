// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "FastGas/Data/FGTypesCore.h"
#include "GameFramework/Actor.h"
#include "FGEventItem.generated.h"

UCLASS()
class FASTGAS_API AFGEventItem : public AActor
{
public:
	GENERATED_UCLASS_BODY()




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(BluEprintReadOnly, VisibleAnywhere, Category = "GAS", meta = ( ExposeOnSpawn = true ))
	FFGGameplayEffectContainer Container;
	UPROPERTY(BluEprintReadOnly, VisibleAnywhere, Category = "GAS", meta = (ExposeOnSpawn = true))
	FGameplayEventData EventData;
	UPROPERTY(BluEprintReadOnly, VisibleAnywhere, Category = "GAS", meta = (ExposeOnSpawn = true))
	int32 Level;
};

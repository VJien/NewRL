// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FastGas/SceneItem/FGEventItem.h"
#include "GameFramework/Actor.h"
#include "RLSceneDynamicItem.generated.h"

UCLASS()
class SCIFI_RL_API ARLSceneDynamicItem : public AFGEventItem
{
	GENERATED_UCLASS_BODY()

public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EffectsID = NAME_None;
};

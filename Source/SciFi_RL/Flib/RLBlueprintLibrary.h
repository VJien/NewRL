// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RLBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SCIFI_RL_API URLBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static void SetWidgetComponentClass(class UWidgetComponent* WidgetComponent, TSubclassOf<class UUserWidget> NewClass);
};

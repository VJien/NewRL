// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS/FGAttributeSetBase.h"
#include "UObject/Object.h"
#include "FGSettings.generated.h"

/**
 * 
 */
UCLASS(config = FastGas,defaultconfig, Blueprintable, BlueprintType)
class FASTGAS_API UFGSettings : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UFGSettings* Get()
	{
		return GetMutableDefault<UFGSettings>();
	}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Config)
	FString ByCallerGameplayEffectPath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Config)
	TSoftClassPtr<UFGAttributeSetBase> AttributeSetClass;
};

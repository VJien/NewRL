// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Factories/Factory.h"
#include "UObject/Object.h"
#include "FGGameplayEffectFactory.generated.h"

/**
 * 
 */
UCLASS(HideCategories = Object)
class FASTGASEDITOR_API UFGGameplayEffectFactory : public UFactory
{
	GENERATED_BODY()

public:
	UFGGameplayEffectFactory(const FObjectInitializer& ObjectInitializer);
	virtual ~UFGGameplayEffectFactory();

public:
	UPROPERTY(EditAnywhere, Category = "GAS")
	TEnumAsByte<EBlueprintType> mBlueprintType;
	
	UPROPERTY(EditAnywhere, Category = "GAS")
	TSubclassOf<UGameplayEffect> ParentClass;

public:
	// override UFactory function
	virtual bool ConfigureProperties()override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn,FName InCallingContext)override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGDatatableFactory.generated.h"

/**
 * 
 */
UCLASS()
class FASTGASEDITOR_API UFGDatatableFactory : public UFactory
{
	GENERATED_BODY()
public:
	UFGDatatableFactory(const FObjectInitializer& ObjectInitializer);
	virtual ~UFGDatatableFactory();

public:
	UPROPERTY(BlueprintReadWrite, Category = "FG Data Table Factory")
	const class UScriptStruct* Struct;

public:
	// override UFactory function
	virtual bool ConfigureProperties()override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn,FName InCallingContext)override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn);
};

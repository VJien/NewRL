// Fill out your copyright notice in the Description page of Project Settings.


#include "FGDatatableFactory.h"

UFGDatatableFactory::UFGDatatableFactory(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	bCreateNew = false;
	bEditAfterNew = true;

	// 这个Factory托管的类型
	SupportedClass = UDataTable::StaticClass();
}

UFGDatatableFactory::~UFGDatatableFactory()
{
}

bool UFGDatatableFactory::ConfigureProperties()
{
	return true;
}

UObject* UFGDatatableFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags,
	UObject* InContext, FFeedbackContext* InWarn, FName InCallingContext)
{
	UDataTable* DataTable = nullptr;
	if (Struct && ensure(SupportedClass == InClass))
	{
		ensure(0 != (RF_Public & InFlags));
		DataTable = NewObject<UDataTable>(InParent, InName, InFlags);
		if (DataTable)
		{
			DataTable->RowStruct = const_cast<UScriptStruct*>(Struct);
		}
	}
	return DataTable;
}

UObject* UFGDatatableFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags,
	UObject* InContext, FFeedbackContext* InWarn)
{
	return FactoryCreateNew(InClass, InParent, InName, InFlags, InContext, InWarn, NAME_None);
}

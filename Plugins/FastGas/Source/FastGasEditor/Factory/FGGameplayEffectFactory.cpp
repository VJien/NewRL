// Fill out your copyright notice in the Description page of Project Settings.


#include "FGGameplayEffectFactory.h"

#include "KismetCompilerModule.h"
#include "Kismet2/KismetEditorUtilities.h"
#define LOCTEXT_NAMESPACE "GameplayEffectFactory"


UFGGameplayEffectFactory::UFGGameplayEffectFactory(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;

	// 这个Factory托管的类型
	SupportedClass = UGameplayEffect::StaticClass();
	ParentClass = UGameplayEffect::StaticClass();
	
}

UFGGameplayEffectFactory::~UFGGameplayEffectFactory()
{

}

bool UFGGameplayEffectFactory::ConfigureProperties()
{
	return true;
}

UObject* UFGGameplayEffectFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn,FName InCallingContext)
{

	return FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), InCallingContext);
	
}

UObject* UFGGameplayEffectFactory::FactoryCreateNew(UClass* InClass,UObject* InParent,FName InName,EObjectFlags InFlags,UObject* InContext,FFeedbackContext* InWarn)
{
	return FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
}

#undef LOCTEXT_NAMESPACE
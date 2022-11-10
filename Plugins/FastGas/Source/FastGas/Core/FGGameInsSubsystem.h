// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "FGGameInsSubsystem.generated.h"


USTRUCT(BlueprintType)
struct FGameplayEffectByCallerData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintType)
	FGameplayTag Tag;
	UPROPERTY(BlueprintType)
	TSubclassOf<UGameplayEffect> GE;


	bool IsValid()const
	{
		return ::IsValid(GE) && Tag.IsValid();
	}
};




UCLASS(Blueprintable, BlueprintType)
class FASTGAS_API UFGGameInsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	FGameplayEffectByCallerData FindGameplayEffectByCallerData(FGameplayAttribute Attribute, TEnumAsByte<EGameplayModOp::Type> Type);
protected:
	void InitGE_ByCallerMap();
	
	UPROPERTY()
	TMap<FGameplayAttribute, FGameplayEffectByCallerData> GE_ByCallerMap_Add;
	UPROPERTY()
	TMap<FGameplayAttribute, FGameplayEffectByCallerData> GE_ByCallerMap_Multi;
	UPROPERTY()
	TMap<FGameplayAttribute, FGameplayEffectByCallerData> GE_ByCallerMap_Override;
};

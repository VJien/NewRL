// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Data/FGTypesCore.h"
#include "UObject/Object.h"
#include "FG_GEEC_Base.generated.h"




UCLASS()
class FASTGAS_API UFG_GEEC_Base : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UFG_GEEC_Base();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "GEEC")
		float CalcPhysicsMitigatedDamage(EFGDamageStatus& OutDamageStatus, float  UnmitigatedDamage, float TargetArmor, float critPro, float critMul, float ReducePercent = 0.0f, float PhysicsResistance = 0.0f)const;
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "GEEC")
		float CalcMagicMitigatedDamage(EFGDamageStatus& OutDamageStatus, float UnmitigatedDamage, float critPro, float critMul, float ReducePercent = 0.0f, float Resistance = 0.0f)const ;



	UPROPERTY(EditAnywhere, Category = "GEEC")
	bool bDebug = true;
};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "UObject/Object.h"
#include "FGTargetType.generated.h"

class AFGCharacter;
/**
 * 
 */
/**
 * 这个类是作为辅助类而存在的
 * 目的是通过蓝图来重写函数最终实现找到目标类
 * 此类不需要实例化
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class FASTGAS_API UFGTargetType : public UObject
{
	GENERATED_BODY()

public: 
	UFGTargetType() {}

	UFUNCTION(BlueprintNativeEvent)
		void GetTargets(AFGCharacter* SourceCharacter, AActor* SourceActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};
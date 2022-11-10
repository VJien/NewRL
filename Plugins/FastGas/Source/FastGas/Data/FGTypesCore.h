// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "UObject/Object.h"
#include "FGTypesCore.generated.h"

class UFGTargetType;
DECLARE_LOG_CATEGORY_EXTERN(FGLog, Log, All);

#define FGLOG(l,...) UE_LOG(FGLog, Log, TEXT(l), ...)
#define FGWARNING(l,...) UE_LOG(FGLog, Warning, TEXT(l), ...)
#define FGERROR(l,...) UE_LOG(FGLog, Error, TEXT(l), ...)





UENUM(BlueprintType)
enum class EFGAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Ability1,
	Ability2,

};


/**
 * 用于配置每个GA获取目标的方式
 * 定义了 GE, Tag 和 目标信息
 */
USTRUCT(BlueprintType)
struct FASTGAS_API FFGGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FFGGameplayEffectContainer() {}

	/********** 目标类型*********/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TSubclassOf<UFGTargetType> TargetType;

	/** 应用到目标上的GE */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};

/** 用来处理SRGameplayEffectContainer数据传递的结构体,参考GE和GA等都会有类似的Spec类*/
USTRUCT(BlueprintType)
struct FASTGAS_API FFGGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:
	FFGGameplayEffectContainerSpec() {}

	/** 目标数据 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	FGameplayAbilityTargetDataHandle TargetData;

	/** 应用到目标是GESpec */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

	/** 是否有有效的GE */
	bool HasValidEffects() const;

	/**是否有目标 */
	bool HasValidTargets() const;

	/** 添加 目标数据*/
	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};




UENUM(BlueprintType)
enum class EFGDamageType : uint8
{
	None,
	Physics,
	Fire,
	Ice,
	Dark,
	Nature,
	Arcane
};



UENUM(BlueprintType)
enum class EFGDamageStatus : uint8
{
	Normal,
	//暴击
	Crit,
	//真实伤害
	Realdamage,
	//暴击的真实伤害
	CritRealdamage
};



/*
* 伤害参数
*/
USTRUCT(BlueprintType)
struct FASTGAS_API FFGDamageParameter
{
	GENERATED_BODY()
public:
	FFGDamageParameter() {};
	FFGDamageParameter(const FHitResult& hit, float inUnmit, float inMit, EFGDamageType inType, EFGDamageStatus inStatus)
	:HitResult(hit), UnmitigatedDamage(inUnmit), MitigatedDamage(inMit), Type(inType), Status(inStatus)
	{}
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	FHitResult HitResult;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	float UnmitigatedDamage = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	float MitigatedDamage = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	EFGDamageType Type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	EFGDamageStatus Status;
	
};

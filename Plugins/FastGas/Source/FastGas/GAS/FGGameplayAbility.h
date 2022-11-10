// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/FGTypesCore.h"
#include "UObject/Object.h"
#include "FGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class FASTGAS_API UFGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)override;
public:
	/*通过FFGGameplayEffectContainer构造FSRGameplayEffectContainerSpec*/
	UFUNCTION(BlueprintCallable, Category = "SR|AbilityBase", meta = (AutoCreateRefTerm = "EventData"))
		virtual FFGGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FFGGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
	//通过Tag从EffectContainerMap中找到FSRGameplayEffectContainer, 然后再构建spec
	UFUNCTION(BlueprintCallable, Category = "SR|AbilityBase", meta = (AutoCreateRefTerm = "EventData"))
		virtual FFGGameplayEffectContainerSpec MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
	//通过spec应用GE
	UFUNCTION(BlueprintCallable, Category = "SR|AbilityBase")
		virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FFGGameplayEffectContainerSpec& ContainerSpec);
	/*
	* 通过tag来应用GE, 
	* 实际上就是通过MakeEffectContainerSpec()来构建spec再用ApplyEffectContainerSpec()来应用
	*/
	UFUNCTION(BlueprintCallable, Category = "SR|AbilityBase", meta = (AutoCreateRefTerm = "EventData"))
		virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);


	//标签对应的GE信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag, FFGGameplayEffectContainer> EffectContainerMap;



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	FString AbilityName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	bool bAutoActivate = false;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EFGAbilityInputID InputID;
};

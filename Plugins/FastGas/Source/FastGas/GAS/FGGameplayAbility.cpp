// Fill out your copyright notice in the Description page of Project Settings.


#include "FGGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "FGComponent.h"
#include "Core/FGCharacter.h"
#include "Data/FGTargetType.h"

void UFGGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	if (bAutoActivate)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

FFGGameplayEffectContainerSpec UFGGameplayAbility::MakeEffectContainerSpecFromContainer(
	const FFGGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	FFGGameplayEffectContainerSpec resultSpec;
	AActor* OwningActor = GetOwningActorFromActorInfo();
	AFGCharacter* OwningChar = Cast<AFGCharacter>(OwningActor);
	UFGComponent* OwningASC = Cast<UFGComponent>(GetAbilitySystemComponentFromActorInfo());

	if (OwningASC)
	{
		//TargetType
		if (Container.TargetType.Get())
		{
			TArray<FHitResult> HitResults;
			TArray<AActor*> TargetActors;
			const UFGTargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
			AActor* AvatarActor = GetAvatarActorFromActorInfo();
			
			TargetTypeCDO->GetTargets(OwningChar, AvatarActor, EventData, HitResults, TargetActors);
			
			resultSpec.AddTargets(HitResults, TargetActors);
		}                                          
		//OverrideGameplayLevel = -1
		if (OverrideGameplayLevel == INDEX_NONE)
		{
			OverrideGameplayLevel = GetAbilityLevel();
		}

		for (const  TSubclassOf<UGameplayEffect>& c : Container.TargetGameplayEffectClasses)
		{
			resultSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(c, OverrideGameplayLevel));
		}
	}
	return resultSpec;
}

FFGGameplayEffectContainerSpec UFGGameplayAbility::MakeEffectContainerSpec(FGameplayTag ContainerTag,
	const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	FFGGameplayEffectContainer* FoundContainer = EffectContainerMap.Find(ContainerTag);

	if (FoundContainer)
	{
		return MakeEffectContainerSpecFromContainer(*FoundContainer, EventData, OverrideGameplayLevel);
	}
	return FFGGameplayEffectContainerSpec();
}

TArray<FActiveGameplayEffectHandle> UFGGameplayAbility::ApplyEffectContainerSpec(
	const FFGGameplayEffectContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> AllEffects;
	for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
	{
		AllEffects.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TargetData));
	}
	return AllEffects;
}

TArray<FActiveGameplayEffectHandle> UFGGameplayAbility::ApplyEffectContainer(FGameplayTag ContainerTag,
	const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	FFGGameplayEffectContainerSpec Spec = MakeEffectContainerSpec(ContainerTag, EventData, OverrideGameplayLevel);
	return ApplyEffectContainerSpec(Spec);
}

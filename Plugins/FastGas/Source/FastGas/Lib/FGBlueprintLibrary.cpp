// Fill out your copyright notice in the Description page of Project Settings.


#include "Lib/FGBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AssetToolsModule.h"
#include "JsonObjectConverter.h"
#include "Data/FGTargetType.h"
#include "Core/FGCharacter.h"
#include "GAS/FGComponent.h"
#include "GAS/FGGameplayAbility.h"
#include "JsonObjectConverter.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Core/FGGameInsSubsystem.h"
#include "Core/FGSettings.h"
#include "Factories/DataTableFactory.h"
#include "GAS/FGAttributeSetBase.h"

TArray<FGameplayAbilitySpec> UFGBlueprintLibrary::GetActivableAbilities(UAbilitySystemComponent* ASC)
{
	if (ASC)
	{
		return ASC->GetActivatableAbilities();
	}
	return TArray<FGameplayAbilitySpec>{};
}

int32 UFGBlueprintLibrary::GetAbilityLevelBySpec(FGameplayAbilitySpec Spec)
{
	return Spec.Level;
}

void UFGBlueprintLibrary::CancelAbilityWithTag(UAbilitySystemComponent* AbilityComponent,
                                               const FGameplayTagContainer& WithTags,
                                               const FGameplayTagContainer& WithoutTags, UGameplayAbility* Ignore)
{
	if (!AbilityComponent)
	{
		return;
	}
	AbilityComponent->CancelAbilities(&WithTags, &WithoutTags, Ignore);
}

void UFGBlueprintLibrary::CancelAllAbilities(UAbilitySystemComponent* AbilityComponent,
                                             UGameplayAbility* Ignore /*= nullptr*/)
{
	if (!AbilityComponent)
	{
		return;
	}
	AbilityComponent->CancelAllAbilities(Ignore);
}

void UFGBlueprintLibrary::CancelAbility(UAbilitySystemComponent* AbilityComponent, UGameplayAbility* Ability)
{
	if (!AbilityComponent || !Ability)
	{
		return;
	}
	AbilityComponent->CancelAbility(Ability);
}

void UFGBlueprintLibrary::CancelAbilityHandle(UAbilitySystemComponent* AbilityComponent,
                                              const FGameplayAbilitySpecHandle& AbilityHandle)
{
	if (!AbilityComponent)
	{
		return;
	}
	AbilityComponent->CancelAbilityHandle(AbilityHandle);
}

void UFGBlueprintLibrary::CancelAbilitySpec(UAbilitySystemComponent* AbilityComponent,
                                            const FGameplayAbilitySpec& AbilityHandle)
{
	if (!AbilityComponent)
	{
		return;
	}

	AbilityComponent->CancelAbilityHandle(AbilityHandle.Handle);
}


void UFGBlueprintLibrary::GetActivatableGameplayAbilitySpecsByAllMatchingTags(
	UAbilitySystemComponent* AbilityComponent, const FGameplayTagContainer& GameplayTagContainer,
	TArray<struct FGameplayAbilitySpec>& MatchingGameplayAbilities, bool bOnlyAbilitiesThatSatisfyTagRequirements)
{
	if (!AbilityComponent)
	{
		return;
	}
	TArray<FGameplayAbilitySpec*> returnAbilities;

	AbilityComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(
		GameplayTagContainer, returnAbilities, bOnlyAbilitiesThatSatisfyTagRequirements);
	for (FGameplayAbilitySpec* i : returnAbilities)
	{
		MatchingGameplayAbilities.Add(*i);
	}
}

bool UFGBlueprintLibrary::HasAbilityByTag(UAbilitySystemComponent* AbilityComponent, FGameplayTag Tag)
{
	if (AbilityComponent)
	{
		auto abilities = AbilityComponent->GetActivatableAbilities();
		if (abilities.Num() == 0)
		{
			return false;
		}
		for (auto GA : abilities)
		{
			if (GA.Ability->AbilityTags.HasTag(Tag))
			{
				return true;
			}
		}
	}
	return false;
}

bool UFGBlueprintLibrary::HasAbilityTag(UAbilitySystemComponent* AbilityComponent, FGameplayTag Tag)
{
	if (AbilityComponent)
	{
		FGameplayTagContainer Tags;
		AbilityComponent->GetOwnedGameplayTags(Tags);
		if (Tags.HasTag(Tag))
		{
			return true;
		}
	}
	return false;
}

bool UFGBlueprintLibrary::AddNewAbility(UFGComponent* AbilityComponent, TSubclassOf<UFGGameplayAbility> AbilityClass,
                                        int32 level)
{
	if (AbilityComponent)
	{
		return AbilityComponent->AddNewAbility(AbilityClass, level);
	}
	return false;
}

bool UFGBlueprintLibrary::RemoveAbilityByClass(UFGComponent* AbilityComponent,
                                               TSubclassOf<UFGGameplayAbility> AbilityClass)
{
	if (AbilityComponent)
	{
		return AbilityComponent->RemoveAbilityByClass(AbilityClass);
	}
	return false;
}

bool UFGBlueprintLibrary::RemoveAbilityByName(UFGComponent* AbilityComponent, const FString& name)
{
	if (AbilityComponent)
	{
		return AbilityComponent->RemoveAbilityByName(name);
	}
	return false;
}

bool UFGBlueprintLibrary::UpgradeAbilityByName(UFGComponent* AbilityComponent, const FString& name, int32 upLevel)
{
	if (AbilityComponent)
	{
		return AbilityComponent->UpgradeAbilityByName(name, upLevel);
	}
	return false;
}

bool UFGBlueprintLibrary::UpgradeAbilityByClass(UFGComponent* AbilityComponent,
                                                TSubclassOf<UFGGameplayAbility> AbilityClass, int32 upLevel)
{
	if (AbilityComponent)
	{
		return AbilityComponent->UpgradeAbilityByClass(AbilityClass, upLevel);
	}
	return false;
}

int32 UFGBlueprintLibrary::GetAbilityLevelByName(UFGComponent* AbilityComponent, const FString& name)
{
	if (AbilityComponent)
	{
		return AbilityComponent->GetAbilityLevelByName(name);
	}
	return -1;
}

int32 UFGBlueprintLibrary::GetAbilityLevelByClass(UFGComponent* AbilityComponent,
                                                  TSubclassOf<UFGGameplayAbility> AbilityClass)
{
	if (AbilityComponent)
	{
		return AbilityComponent->GetAbilityLevelByClass(AbilityClass);
	}
	return -1;
}

UFGGameplayAbility* UFGBlueprintLibrary::GetAbilityObjectByName(UFGComponent* AbilityComponent, const FString& name)
{
	if (AbilityComponent)
	{
		return AbilityComponent->GetAbilityObjectByName(name);
	}
	return nullptr;
}

bool UFGBlueprintLibrary::HasAbility(UFGComponent* AbilityComponent, const FString& name)
{
	if (AbilityComponent)
	{
		return AbilityComponent->HasAbility(name);
	}
	return false;
}

bool UFGBlueprintLibrary::HasAbilityByClass(UFGComponent* AbilityComponent,
                                            TSubclassOf<UFGGameplayAbility> AbilityClass)
{
	if (AbilityComponent)
	{
		return AbilityComponent->HasAbilityByClass(AbilityClass);
	}
	return false;
}

void UFGBlueprintLibrary::ExecuteGameplayCueLocal(UAbilitySystemComponent* AbilityComponent,
                                                  const FGameplayTag& GameplayCueTag,
                                                  const FGameplayCueParameters& GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		AbilityComponent->GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::Executed, GameplayCueParameters);
}

void UFGBlueprintLibrary::RemoveGameplayCueLocal(UAbilitySystemComponent* AbilityComponent,
                                                 const FGameplayTag& GameplayCueTag,
                                                 const FGameplayCueParameters& GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		AbilityComponent->GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::Removed, GameplayCueParameters);
}

void UFGBlueprintLibrary::AddGameplayCueLocal(UAbilitySystemComponent* AbilityComponent,
                                              const FGameplayTag& GameplayCueTag,
                                              const FGameplayCueParameters& GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		AbilityComponent->GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::OnActive, GameplayCueParameters);
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		AbilityComponent->GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::WhileActive, GameplayCueParameters);
}

float UFGBlueprintLibrary::GetScalableFloatValue(FScalableFloat ScaleFloat, int32 level)
{
	return ScaleFloat.GetValueAtLevel(level);
}

FFGGameplayEffectContainerSpec UFGBlueprintLibrary::AddTargetsToEffectContainerSpec(
	const FFGGameplayEffectContainerSpec& ContainerSpec, const TArray<FHitResult>& HitResults,
	const TArray<AActor*>& TargetActors)
{
	FFGGameplayEffectContainerSpec newSpec = ContainerSpec;
	newSpec.AddTargets(HitResults, TargetActors);
	return newSpec;
}

TArray<FActiveGameplayEffectHandle> UFGBlueprintLibrary::ApplyEffectContainerSpec(
	const FFGGameplayEffectContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> out;
	for (const FGameplayEffectSpecHandle& spec : ContainerSpec.TargetGameplayEffectSpecs)
	{
		if (spec.IsValid())
		{
			for (TSharedPtr<FGameplayAbilityTargetData> data : ContainerSpec.TargetData.Data)
			{
				out.Append(data->ApplyGameplayEffectSpec(*spec.Data.Get()));
			}
		}
	}
	return out;
}

bool UFGBlueprintLibrary::HasEffects(const FFGGameplayEffectContainerSpec& ContainerSpec)
{
	return ContainerSpec.HasValidEffects();
}

bool UFGBlueprintLibrary::HasTargets(const FFGGameplayEffectContainerSpec& ContainerSpec)
{
	return ContainerSpec.HasValidTargets();
}


FFGGameplayEffectContainerSpec UFGBlueprintLibrary::MakeEffectContainerExtra(
	AActor* ownerActor, const FFGGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 level)
{
	FFGGameplayEffectContainerSpec resultSpec;
	if (!ownerActor)
	{
		return resultSpec;
	}
	AFGCharacter* OwningChar = Cast<AFGCharacter>(ownerActor);
	UFGComponent* OwningASC = Cast<UFGComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ownerActor));

	if (OwningASC)
	{
		if (Container.TargetType.Get())
		{
			TArray<FHitResult> HitResults;
			TArray<AActor*> TargetActors;
			const UFGTargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
			AActor* AvatarActor = ownerActor;
			TargetTypeCDO->GetTargets(OwningChar, AvatarActor, EventData, HitResults, TargetActors);
			resultSpec.AddTargets(HitResults, TargetActors);
		}
		//OverrideGameplayLevel = -1
		if (level == INDEX_NONE)
		{
			level = 1;
		}

		for (const TSubclassOf<UGameplayEffect>& c : Container.TargetGameplayEffectClasses)
		{
			resultSpec.TargetGameplayEffectSpecs.Add(
				(OwningASC->MakeOutgoingSpec(c, level, FGameplayEffectContextHandle())));
		}
	}
	return resultSpec;
}

bool UFGBlueprintLibrary::TryGetActorInfo(UAbilitySystemComponent* AbilityComponent,
                                          FGameplayAbilityActorInfo& ActorInfo)
{
	if (AbilityComponent && AbilityComponent->AbilityActorInfo.IsValid())
	{
		ActorInfo = *AbilityComponent->AbilityActorInfo.Get();
		return true;
	}
	return false;
}

bool UFGBlueprintLibrary::TryApplyGameplayEffectByCaller(UAbilitySystemComponent* AbilitySystemComponent,
                                                         FGameplayAttribute Attribute, float NewValue,
                                                         TEnumAsByte<EGameplayModOp::Type> Type)
{
	if (!AbilitySystemComponent)
	{
		return false;
	}

	auto FGSubsys = AbilitySystemComponent->GetWorld()->GetGameInstance()->GetSubsystem<UFGGameInsSubsystem>();
	if (!FGSubsys)
	{
		return false;
	}
	auto ByCallerData = FGSubsys->FindGameplayEffectByCallerData(Attribute, Type);
	if (!ByCallerData.IsValid())
	{
		return false;
	}

	FGameplayEffectContextHandle Context;
	auto SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ByCallerData.GE, 0, Context);
	FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
	Spec->SetSetByCallerMagnitude(ByCallerData.Tag, NewValue);
	return AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec).IsValid();


	/*
	if(UFGSettings* Setting = UFGSettings::Get())
	{
		const FString& AssetPath = Setting->ByCallerGameplayEffectPath;
		
		IAssetRegistry* AssetRegistry = IAssetRegistry::Get();
		if (!AssetRegistry)
		{
			return false;
		}
		TArray<FAssetData> AssetData;
		FAssetData MatchedAsset;
		if (AssetRegistry->GetAssetsByPath(*AssetPath,AssetData))
		{
			for (const FAssetData& Asset: AssetData)
			{
				if (Asset.AssetName.ToString().Contains(Attribute.GetName()))
				{
					MatchedAsset = Asset;
					break;
				}
			}
		}
		if (!MatchedAsset.IsValid())
		{
			return false;
		}
		auto BpAsset = Cast<UBlueprint>(MatchedAsset.GetAsset());
		if (!BpAsset || !BpAsset->GeneratedClass->IsChildOf(UGameplayEffect::StaticClass()))
		{
			return  false;
		}
		auto GE = Cast<UGameplayEffect>(BpAsset->GeneratedClass->ClassDefaultObject);
		if (!GE)
		{
			return false;
		}
		FGameplayTag Tag;
		auto Data = GE->Modifiers[0].ModifierMagnitude.GetSetByCallerFloat();
		Tag = Data.DataTag;
		FGameplayEffectContextHandle Context;
		auto SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GE->GetClass(),0,Context);
		FGameplayEffectSpec* Spec = SpecHandle.Data.Get();
		Spec->SetSetByCallerMagnitude(Tag, NewValue);
		return AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec).IsValid();
		
	}
	return false;*/
}

bool UFGBlueprintLibrary::TryApplyGameplayEffectRumtime(UAbilitySystemComponent* AbilitySystemComponent,
                                                                 FGameplayAttribute Attribute, float NewValue,
                                                                 TEnumAsByte<EGameplayModOp::Type> Type)
{
	auto GE = NewObject<UGameplayEffect>();
	if (!GE)
	{
		return false;
	}
	FGameplayModifierInfo Info;
	Info.Attribute = Attribute;
	Info.ModifierOp = Type;
	FScalableFloat ModValue(NewValue);
	FGameplayEffectModifierMagnitude Mag(ModValue);
	Info.ModifierMagnitude = Mag;
	GE->Modifiers.Emplace(Info);
	FGameplayEffectContextHandle Context;

	return AbilitySystemComponent->ApplyGameplayEffectToSelf(GE,0,Context).IsValid();
}


FString UFGBlueprintLibrary::DamageTypeToString(EFGDamageType type)
{
	return FGEnumToString<EFGDamageType>("EFGDamageType", type, true);
}

EFGDamageType UFGBlueprintLibrary::StringToDamageType(const FString& name)
{
	return FGStringToEnum<EFGDamageType>("EFGDamageType", name);
}

void UFGBlueprintLibrary::GenericUStructToJsonObjectString(const UStruct* StructDefinition, const void* Struct,
                                                           FString& OutJsonString, int64 CheckFlags, int64 SkipFlags)
{
	FJsonObjectConverter::UStructToJsonObjectString(StructDefinition, Struct, OutJsonString, CheckFlags, SkipFlags);
}

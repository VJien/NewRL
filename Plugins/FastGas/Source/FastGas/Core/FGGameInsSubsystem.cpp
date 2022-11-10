// Fill out your copyright notice in the Description page of Project Settings.


#include "FGGameInsSubsystem.h"

#include "AbilitySystemGlobals.h"
#include "FGSettings.h"
#include "GAS/FGAttributeSetBase.h"
#include "GameplayTagsManager.h"
#include "AssetRegistry/IAssetRegistry.h"
PRAGMA_DISABLE_OPTIMIZATION
void UFGGameInsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UAbilitySystemGlobals::Get().InitGlobalData();
	InitGE_ByCallerMap();
}

FGameplayEffectByCallerData UFGGameInsSubsystem::FindGameplayEffectByCallerData(FGameplayAttribute Attribute,TEnumAsByte<EGameplayModOp::Type> Type)
{
	const FGameplayEffectByCallerData Result;
	switch (Type)
	{
	case EGameplayModOp::Additive:
		{
			auto V = GE_ByCallerMap_Add.Find(Attribute);
			return V? *V: Result;
		}
	case EGameplayModOp::Multiplicitive:
		{
			auto V = GE_ByCallerMap_Multi.Find(Attribute);
			return V? *V: Result;
		}
	case EGameplayModOp::Override:
		{
			auto V = GE_ByCallerMap_Override.Find(Attribute);
			return V? *V: Result;
		}
		default:
			return Result;
	}
}


void UFGGameInsSubsystem::InitGE_ByCallerMap()
{
	const auto Setting = UFGSettings::Get();
	if (!Setting)
	{
		return;
	}
	const FString& GEAssetPath = Setting->ByCallerGameplayEffectPath;
	auto AttributeSetClass = LoadClass<UFGAttributeSetBase>(NULL, *Setting->AttributeSetClass.ToString());// Setting->AttributeSetClass.TryLoadClass<UFGAttributeSetBase>();
	if (GEAssetPath.IsEmpty() || !AttributeSetClass)
	{
		return;
	}
	auto AttributeSetCDO= AttributeSetClass->GetDefaultObject();
	UFGAttributeSetBase* AttributesSet = Cast<UFGAttributeSetBase>(AttributeSetCDO);
	if (!AttributesSet)
	{
		return;
	}
	auto Attributes = AttributesSet->ListAllAttribute();
	if (Attributes.Num() == 0)
	{
		return;
	}
	
	UGameplayTagsManager& TagMgr =  UGameplayTagsManager::Get();
	FGameplayTagContainer Tags;
	TagMgr.RequestAllGameplayTags(Tags,false);
	if (Tags.Num() == 0)
	{
		return;
	}
	TArray<FGameplayTag> TagArr;
	Tags.GetGameplayTagArray(TagArr);

	
	IAssetRegistry* AssetRegistry = IAssetRegistry::Get();
	if (!AssetRegistry)
	{
		return;
	}
	TArray<FAssetData> AssetData;
	FAssetData MatchedAsset;
	if (AssetRegistry->GetAssetsByPath(*GEAssetPath,AssetData))
	{
		for (const FAssetData& Asset: AssetData)
		{
			for (auto Att : Attributes)
			{
				FGameplayEffectByCallerData Data;
				auto BpAsset = Cast<UBlueprint>(Asset.GetAsset());
				if (!BpAsset || !BpAsset->GeneratedClass->IsChildOf(UGameplayEffect::StaticClass()))
				{
					break;
				}
				auto GE = Cast<UGameplayEffect>(BpAsset->GeneratedClass->ClassDefaultObject);
				if (!GE)
				{
					break;
				}
				auto ByCallerData = GE->Modifiers[0].ModifierMagnitude.GetSetByCallerFloat();
				Data.Tag = ByCallerData.DataTag;
				Data.GE = GE->GetClass();
				
				if (Asset.AssetName.ToString().Contains(TEXT("Add_") + Att.GetName()))
				{
					GE_ByCallerMap_Add.Emplace(Att,Data);
				}
				else if (Asset.AssetName.ToString().Contains(TEXT("Multi_") + Att.GetName()))
				{
					GE_ByCallerMap_Multi.Emplace(Att,Data);
				}
				else if (Asset.AssetName.ToString().Contains(TEXT("Override_") + Att.GetName()))
				{
					GE_ByCallerMap_Override.Emplace(Att,Data);
				}
			}
		}
	}
}
PRAGMA_ENABLE_OPTIMIZATION
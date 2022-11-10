// Fill out your copyright notice in the Description page of Project Settings.


#include "FGEditorBlueprintLibrary.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "DataTableEditorUtils.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "GameplayTagsModule.h"
#include "IContentBrowserSingleton.h"
#include "FastGasEditor/Factory/FGDatatableFactory.h"
#include "FastGasEditor/Factory/FGGameplayEffectFactory.h"
#include "GAS/FGAttributeSetBase.h"

#if PLATFORM_WINDOWS
#include "DesktopPlatformModule.h"
#endif

#define LOCTEXT_NAMESPACE "FFastGasEditorLibrary"


#if WITH_EDITOR

void UFGEditorBlueprintLibrary::CreateAttributeSetDataTable(TSubclassOf<UAttributeSet> AtttributeSetClass)
{
	
	auto CDO = AtttributeSetClass->GetDefaultObject();
	auto AttSet = Cast<UFGAttributeSetBase>(CDO);
	if (AttSet)
	{
		auto Attributes = AttSet->ListAllAttribute();
		if (Attributes.Num() == 0)
		{
			return;
		}
		UDataTable* DataTable = CreateDatatable_GameplayTag();
		for (auto A: Attributes)
		{
			auto Name = A.GetName();
			auto NewName = TEXT("Attribute.") + Name.Replace(TEXT("_"),TEXT("."));
			
			AddDataTableNewRow_GameplayTagName(DataTable,FName(NewName),FName(NewName));
		}
	}
}

UDataTable* UFGEditorBlueprintLibrary::CreateDatatable_GameplayTag ()
{
	UFGDatatableFactory* Factory = NewObject<UFGDatatableFactory>();
	Factory->Struct = FGameplayTagTableRow::StaticStruct();
	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	UObject* NewAsset = AssetToolsModule.Get().CreateAssetWithDialog( UDataTable::StaticClass(), Factory);
	if (UDataTable* DT = Cast<UDataTable>(NewAsset))
	{
		return DT;
	}

	return nullptr;
}

void UFGEditorBlueprintLibrary::AddDataTableNewRow_GameplayTagName(UDataTable* DataTable, FName RowName, FName Tag)
{
	if (DataTable && DataTable->RowStruct == FGameplayTagTableRow::StaticStruct())
	{
		FDataTableEditorUtils::AddRow(DataTable, RowName);
		FString Context;
		FGameplayTagTableRow* RowData = DataTable->FindRow<FGameplayTagTableRow>(RowName,Context);
		RowData->Tag = Tag;
		DataTable->MarkPackageDirty();
	}
}

void UFGEditorBlueprintLibrary::CreateGameplayEffects(TArray<FGameplayAttribute> Attributes, const FString& Path, bool bCreateAdditive, bool bCreateMulti, bool bCreateOverride)
{
	UGameplayTagsManager& TagMgr =UGameplayTagsManager::Get();
	FGameplayTagContainer Tags;
	if (Attributes.Num() == 0)
	{
		return;
	}
	FString PackagePath = Path;
	if (PackagePath.IsEmpty())
	{
		PackagePath = TEXT("/Game/");
	
	}
	
	TagMgr.RequestAllGameplayTags(Tags,false);
	if (Tags.Num() > 0)
	{
		TArray<FGameplayTag> TagArr;
		Tags.GetGameplayTagArray(TagArr);
		TArray<FString> AttTagNames, AttTagNamesReplace;
		for (const FGameplayTag& Tag : TagArr)
		{
			const FString TagName = Tag.GetTagName().ToString();
			if (TagName.StartsWith(TEXT("Attribute.")))
			{
				AttTagNames.Emplace(TagName.RightChop(10));
				AttTagNamesReplace.Emplace(TagName.RightChop(10).Replace(TEXT("."),TEXT("_")));
			}
		}
		TMap<FName, FGameplayAttribute> Tag_Mapping_Att;
		for (auto Att: Attributes)
		{
			if (auto idx = AttTagNamesReplace.Find(Att.GetName()))
			{
				Tag_Mapping_Att.Emplace(AttTagNames[idx], Att);
			}
		}
		
		FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
		UFGGameplayEffectFactory* Factory = NewObject<UFGGameplayEffectFactory>();
		for (auto P : Tag_Mapping_Att)
		{
			if (bCreateAdditive)
			{
				FString AssetName = TEXT("GE_Add_") + P.Key.ToString().Replace(TEXT("."),TEXT("_"));
				FString NewAssetName, NewPath;
				AssetToolsModule.Get().CreateUniqueAssetName(PackagePath,AssetName,NewPath, NewAssetName);
				UObject* NewAsset = AssetToolsModule.Get().CreateAsset(NewAssetName, PackagePath,  UGameplayEffect::StaticClass(), Factory);
				if (auto BP = Cast<UBlueprint>(NewAsset))
				{
					auto GClass = BP->GeneratedClass;
					auto CDO = GClass.GetDefaultObject();
					if (auto GE = Cast<UGameplayEffect>(CDO))
					{
						FGameplayModifierInfo Info;
						Info.Attribute = P.Value;
						Info.ModifierOp = EGameplayModOp::Additive;
						FSetByCallerFloat ByCallerFloat;
						ByCallerFloat.DataName = P.Key;
						ByCallerFloat.DataTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Attribute.") + P.Key.ToString()));
						FGameplayEffectModifierMagnitude Mag(ByCallerFloat);
						Info.ModifierMagnitude = Mag;
						GE->Modifiers.Add(Info);
						GE->MarkPackageDirty();
					}
				}
				
			}
			if (bCreateMulti)
			{
				FString AssetName = TEXT("GE_Mul_") + P.Key.ToString().Replace(TEXT("."),TEXT("_"));
				FString NewAssetName, NewPath;
				AssetToolsModule.Get().CreateUniqueAssetName(PackagePath,AssetName,NewPath, NewAssetName);
				UObject* NewAsset = AssetToolsModule.Get().CreateAsset(NewAssetName, PackagePath,  UGameplayEffect::StaticClass(), Factory);
				if (auto BP = Cast<UBlueprint>(NewAsset))
				{
					auto GClass = BP->GeneratedClass;
					auto CDO = GClass.GetDefaultObject();
					if (auto GE = Cast<UGameplayEffect>(CDO))
					{
						FGameplayModifierInfo Info;
						Info.Attribute = P.Value;
						Info.ModifierOp = EGameplayModOp::Multiplicitive;
						FSetByCallerFloat ByCallerFloat;
						ByCallerFloat.DataName = P.Key;
						ByCallerFloat.DataTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Attribute.") + P.Key.ToString()));
						FGameplayEffectModifierMagnitude Mag(ByCallerFloat);
						Info.ModifierMagnitude = Mag;
						GE->Modifiers.Add(Info);
						GE->MarkPackageDirty();
					}
				}
			}
			if (bCreateOverride)
			{
				FString AssetName = TEXT("GE_Override_") + P.Key.ToString().Replace(TEXT("."),TEXT("_"));
				FString NewAssetName, NewPath;
				AssetToolsModule.Get().CreateUniqueAssetName(PackagePath,AssetName,NewPath, NewAssetName);
				UObject* NewAsset = AssetToolsModule.Get().CreateAsset(NewAssetName, PackagePath,  UGameplayEffect::StaticClass(), Factory);
				if (auto BP = Cast<UBlueprint>(NewAsset))
				{
					auto GClass = BP->GeneratedClass;
					auto CDO = GClass.GetDefaultObject();
					if (auto GE = Cast<UGameplayEffect>(CDO))
					{
						FGameplayModifierInfo Info;
						Info.Attribute = P.Value;
						Info.ModifierOp = EGameplayModOp::Override;
						FSetByCallerFloat ByCallerFloat;
						ByCallerFloat.DataName = P.Key;
						ByCallerFloat.DataTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Attribute.") + P.Key.ToString()));
						FGameplayEffectModifierMagnitude Mag(ByCallerFloat);
						Info.ModifierMagnitude = Mag;
						GE->Modifiers.Add(Info);
						GE->MarkPackageDirty();
					}
				}
			}
			
		}
	}
	
}

void UFGEditorBlueprintLibrary::CreateGameplayEffectsAllAttributes(TSubclassOf<UAttributeSet> AtttributeSetClass, const FString& Path, bool bCreateAdditive,
	bool bCreateMulti, bool bCreateOverride)
{
	auto CDO =AtttributeSetClass->GetDefaultObject();
	auto AttSet = Cast<UFGAttributeSetBase>(CDO);
	if (AttSet)
	{
		auto Attributes = AttSet->ListAllAttribute();
		CreateGameplayEffects(Attributes, Path, bCreateAdditive, bCreateMulti, bCreateOverride);
	}
	
}



void UFGEditorBlueprintLibrary::GenericAddDataTableRow(const void* Data, UDataTable* DataTable, FName RowName)
{
	if (DataTable)
	{
		FDataTableEditorUtils::AddRow(DataTable, RowName);
		FString Context;
		void* Row = DataTable->FindRowUnchecked(RowName);
		const UScriptStruct* StructType = DataTable->GetRowStruct();
		if (StructType != nullptr)
		{
			StructType->CopyScriptStruct(Row, Data);
		}
		DataTable->MarkPackageDirty();
	}
}

FString UFGEditorBlueprintLibrary::OpenWindowsDirectory(const FString& Path)
{
	FString oldPath;
#if PLATFORM_WINDOWS
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	DesktopPlatform->OpenDirectoryDialog(nullptr, TEXT("打开路径"), Path, oldPath);
#endif
	
	return oldPath;
}

#endif




#undef LOCTEXT_NAMESPACE
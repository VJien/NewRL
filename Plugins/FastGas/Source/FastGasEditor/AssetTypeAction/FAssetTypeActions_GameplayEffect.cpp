// Fill out your copyright notice in the Description page of Project Settings.


#include "FAssetTypeActions_GameplayEffect.h"

#include "BlueprintEditorModule.h"
#include "GameplayEffect.h"
#define LOCTEXT_NAMESPACE "AssetTypeActions"
FAssetTypeActions_GameplayEffect::FAssetTypeActions_GameplayEffect(EAssetTypeCategories::Type AsstCategory):m_AssetCategory(AsstCategory)
{
}

FAssetTypeActions_GameplayEffect::~FAssetTypeActions_GameplayEffect()
{
}

FText FAssetTypeActions_GameplayEffect::GetName() const
{
	// Content里右键菜单创建的显示的可创建类型的名字
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_GameplayEffect", "Gameplay Effect");
}

FColor FAssetTypeActions_GameplayEffect::GetTypeColor() const
{
	return FColor::Emerald;
}

UClass* FAssetTypeActions_GameplayEffect::GetSupportedClass() const
{
	return UGameplayEffect::StaticClass();
}

void FAssetTypeActions_GameplayEffect::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithInLevelEditor)
{
	EToolkitMode::Type Mode = EditWithInLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	
		for (auto Object: InObjects)
		{
			if (UBlueprint* Blueprint = Cast<UBlueprint>(Object))
			{
				bool bLetOpen = true;
				if (!Blueprint->SkeletonGeneratedClass || !Blueprint->GeneratedClass)
				{
					bLetOpen = EAppReturnType::Yes == FMessageDialog::Open(EAppMsgType::YesNo, LOCTEXT("FailedToLoadBlueprintWithContinue", "Blueprint could not be loaded because it derives from an invalid class.  Check to make sure the parent class for this blueprint hasn't been removed! Do you want to continue (it can crash the editor)?"));
				}
				if (bLetOpen)
				{
					FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
					TSharedRef< IBlueprintEditor > NewKismetEditor = BlueprintEditorModule.CreateBlueprintEditor(Mode, EditWithInLevelEditor, Blueprint, false);
				}
			}
			else
			{
				FMessageDialog::Open( EAppMsgType::Ok, LOCTEXT("FailedToLoadBlueprint", "Blueprint could not be loaded because it derives from an invalid class.  Check to make sure the parent class for this blueprint hasn't been removed!"));
			}
		}
		
	
	
}

UThumbnailInfo* FAssetTypeActions_GameplayEffect::GetThumbnailInfo(UObject* Asset) const
{
	return NULL;
}
#undef LOCTEXT_NAMESPACE
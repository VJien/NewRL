// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "UObject/Object.h"

/**
 * 
 */

class  FAssetTypeActions_GameplayEffect : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_GameplayEffect(EAssetTypeCategories::Type AsstCategory);
	~FAssetTypeActions_GameplayEffect();

	// IAssetTypeActions Implementation

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,
	                             TSharedPtr<class IToolkitHost> EditWithInLevelEditor = TSharedPtr<
		                             IToolkitHost>()) override;

	virtual UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;
	virtual uint32 GetCategories() override { return m_AssetCategory; } //自定义的标签，可以用系统自带的EAssetTypeCategories::Type

private:
	EAssetTypeCategories::Type m_AssetCategory;
};

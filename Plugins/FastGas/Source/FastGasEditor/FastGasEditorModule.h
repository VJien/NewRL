// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IAssetTools.h"
#include "Modules/ModuleManager.h"

class FFastGasEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;



	void RegisterAssetType(IAssetTools& AssetTools);

private:
	EAssetTypeCategories::Type GEType;//自定义标签
	
};

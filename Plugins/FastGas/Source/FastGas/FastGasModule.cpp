// Copyright Epic Games, Inc. All Rights Reserved.

#include "FastGasModule.h"

#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "Core/FGSettings.h"

#define LOCTEXT_NAMESPACE "FFastGasModule"

class ISettingsModule;

void FFastGasModule::StartupModule()
{
	RegisterSetting();
}

void FFastGasModule::ShutdownModule()
{
	UnregisterSetting();
}

void FFastGasModule::RegisterSetting()
{
	if (ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		
		ISettingsContainerPtr SettingsContainer = SettingModule->GetContainer("Project");
		SettingsContainer->DescribeCategory("Fast GAS Setting",
			LOCTEXT("FGCategoryName", "Fast GAS Catagory"),
			LOCTEXT("FGCategoryDescription", "Game configuration for the Fast GAS game module"));

		ISettingsSectionPtr SettingsSection = SettingModule->RegisterSettings("Project", "Game", "Fast GAS",
			LOCTEXT("Fast GAS SettingsName", "Fast GAS"),
			LOCTEXT("Fast GAS SettingsDescription", "Configure my GameSetting"),
			GetMutableDefault<UFGSettings>());
		
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FFastGasModule::HandleSettingsSaved);
		}
	}
}

void FFastGasModule::UnregisterSetting()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Game", "Fast GAS");
	}
}

bool FFastGasModule::HandleSettingsSaved()
{
	UFGSettings* s = GetMutableDefault<UFGSettings>();
	if (s)
	{
		s->SaveConfig();
		return true;
	}
	return false;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFastGasModule, FastGas)

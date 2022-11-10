#include "FastGasEditorModule.h"

#include "ISettingsModule.h"
#include "AssetTypeAction/FAssetTypeActions_GameplayEffect.h"
#include "Core/FGSettings.h"


#define LOCTEXT_NAMESPACE "FFastGasEditorModule"


void FFastGasEditorModule::StartupModule()
{
	IAssetTools& AssetToolsInstance = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	//创建自定义标签，可以本地化翻译
	GEType= AssetToolsInstance.RegisterAdvancedAssetCategory(TEXT("Fast GAS"), LOCTEXT("Fast GAS AssetCategory", "Fast GAS"));
	RegisterAssetType(AssetToolsInstance);

}

void FFastGasEditorModule::ShutdownModule()
{
	
}

void FFastGasEditorModule::RegisterAssetType(IAssetTools& AssetTools)
{
	TSharedRef<IAssetTypeActions> GEBlueprint = MakeShareable(new FAssetTypeActions_GameplayEffect(GEType));
	//注册资源行为类
	AssetTools.RegisterAssetTypeActions(GEBlueprint);
	//m_CreatedAssetTypeActions.Add(StateMachineBlueprint);
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFastGasEditorModule, FastGasEditor)
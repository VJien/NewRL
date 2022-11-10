// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SciFi_RL : ModuleRules
{
	public SciFi_RL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"FastGas", 
			"Niagara",
			"UMG",
			
		});

		PrivateIncludePaths.AddRange(
			new string[] {
			
				// ... add other private include paths required here ...
			}
		);
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

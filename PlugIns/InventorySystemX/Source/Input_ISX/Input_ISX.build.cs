/*
* Inventory System X
*
* Copyright (C) 2023-2025 Mykhailo Oliinyk <m19tes@gmail.com> All Rights Reserved.
*/

using UnrealBuildTool;

public class Input_ISX : ModuleRules
{
	public Input_ISX(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"DeveloperSettings"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"SlateCore",
			"Slate",
			"ApplicationCore",
		
		});

		PublicIncludePaths.AddRange(new string[] { ModuleDirectory + "/Public" });
		PrivateIncludePaths.AddRange(new string[] { ModuleDirectory + "/Private" });
	}
}
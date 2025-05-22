// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PJNightmare : ModuleRules
{
	public PJNightmare(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GoogleTest",
			"VRM4UCapture"
		});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput" ,
			"HeadMountedDisplay", 
			"UMG", 
			"Slate", 
			"SlateCore", 
			"OnlineSubsystem", 
			"OnlineSubsystemSteam", 
			"GameplayTags", 
			"GameplayTasks",
			"VRM4U",
			"VRM4ULoader",
			//"VRM4UEditor"
			
		});
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyTraining_Project : ModuleRules
{
	public MyTraining_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}

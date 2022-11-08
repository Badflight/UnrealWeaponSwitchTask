// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UNREALTASK6 : ModuleRules
{
	public UNREALTASK6(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DiabloLike : ModuleRules
{
	public DiabloLike(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}

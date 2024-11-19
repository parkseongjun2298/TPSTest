// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootingGame : ModuleRules
{
	public ShootingGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","UMG","NavigationSystem", "AIModule","GameplayTasks" });
	}
}

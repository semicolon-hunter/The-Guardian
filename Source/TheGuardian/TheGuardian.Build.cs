// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheGuardian : ModuleRules
{
	public TheGuardian(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TheGuardian",
			"TheGuardian/Variant_Platforming",
			"TheGuardian/Variant_Platforming/Animation",
			"TheGuardian/Variant_Combat",
			"TheGuardian/Variant_Combat/AI",
			"TheGuardian/Variant_Combat/Animation",
			"TheGuardian/Variant_Combat/Gameplay",
			"TheGuardian/Variant_Combat/Interfaces",
			"TheGuardian/Variant_Combat/UI",
			"TheGuardian/Variant_SideScrolling",
			"TheGuardian/Variant_SideScrolling/AI",
			"TheGuardian/Variant_SideScrolling/Gameplay",
			"TheGuardian/Variant_SideScrolling/Interfaces",
			"TheGuardian/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

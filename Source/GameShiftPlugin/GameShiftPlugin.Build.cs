// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameShiftPlugin : ModuleRules
{
	public GameShiftPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Json",
                "CoreUObject",
                "Engine",
                "HTTP",
				// ... add other public dependencies that you statically link with here ...
			}
			);


        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.AddRange(new string[] {
                "Settings",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "Json",
                "HTTP"
            });
        }
        else
        {
            PrivateDependencyModuleNames.AddRange(
               new string[]
               {
                    "CoreUObject",
                    "Engine",
                    "Slate",
                    "SlateCore",
                    "Json",
                    "HTTP"
                   // ... add private dependencies that you statically link with here ...	
               }
           );
        }
       
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}

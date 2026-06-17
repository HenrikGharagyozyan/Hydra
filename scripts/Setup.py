import os
import subprocess
import platform

from SetupPython import PythonConfiguration as PythonRequirements

# Make sure everything we need for the setup is installed
PythonRequirements.Validate()

from SetupVulkan import VulkanConfiguration as VulkanRequirements

os.chdir('./../')  # Change from scripts directory to root

VulkanRequirements.Validate()

system = platform.system()

if system == "Windows":
    print("\nRunning premake (Windows)...")
    subprocess.call([os.path.abspath("./scripts/Win-GenProjects.bat"), "nopause"])

elif system == "Linux":
    print("\nRunning premake (Linux)...")
    premakePath = os.path.abspath("./vendor/premake/bin/premake5")
    if os.path.exists(premakePath):
        subprocess.call([premakePath, "gmake2"])
    else:
        print(f"ERROR: premake5 not found at {premakePath}")
        print("Please ensure premake5 is available for Linux.")

elif system == "Darwin":
    print("\nRunning premake (macOS)...")
    premakePath = os.path.abspath("./vendor/premake/bin/premake5")
    if os.path.exists(premakePath):
        subprocess.call([premakePath, "xcode4"])
    else:
        print(f"ERROR: premake5 not found at {premakePath}")
        print("Please ensure premake5 is available for macOS.")

else:
    print(f"\nUnknown platform: {system}. Skipping project generation.")

print("\nSetup completed!")
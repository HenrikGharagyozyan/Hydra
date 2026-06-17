import os
import sys
import subprocess

VULKAN_SDK = os.environ.get('VULKAN_SDK')

def CheckVulkanSDK():
    # На Linux проверяем наличие переменной или стандартных путей
    if sys.platform != "win32":
        # На Linux пакет часто настраивает пути автоматически, либо мы проверяем vulkaninfo
        try:
            subprocess.run(["vulkaninfo"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return True
        except FileNotFoundError:
            print("Vulkan SDK (or vulkan-tools) not found! Please run: sudo apt install vulkan-sdk")
            return False

    # --- Ниже идёт логика ТОЛЬКО для Windows ---
    if VULKAN_SDK is None:
        print("You don't have the Vulkan SDK installed!")
        InstallVulkanPrompt()
        return False
    
    return True
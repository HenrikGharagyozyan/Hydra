import os
import sys
import subprocess
import CheckPython

# Проверяем пакеты pip
CheckPython.ValidatePackages()

import Vulkan

# Переходим в корень проекта
os.chdir('../')

# Проверка Vulkan SDK
if not Vulkan.CheckVulkanSDK():
    print("Vulkan SDK ready status: FAILED")
    sys.exit(1)

print("Running premake...")
if sys.platform == "win32":
    # Для Windows запускаем exe и генерируем решение VS
    subprocess.call(["vendor/premake/bin/premake5.exe", "vs2022"]) 
else:
    # Для Linux используем системный или локальный premake5 и генерируем Makefiles
    # Если premake5 установлен в систему, можно просто "premake5"
    subprocess.call(["premake5", "gmake2"])
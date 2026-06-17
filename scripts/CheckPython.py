import subprocess
import sys
import pkg_resources

def install(package):
    print(f"Installing {package} module...")
    # Автоматически выбираем правильное имя интерпретатора
    python_exe = sys.executable 
    subprocess.check_call([python_exe, '-m', 'pip', 'install', package])
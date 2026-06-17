#!/usr/bin/env python3
"""
Universal entry point for project setup.
Works on Windows, Linux, and macOS.

Usage:
  Windows : python Setup.py
  Linux   : python3 Setup.py
  macOS   : python3 Setup.py
"""

import subprocess
import sys
import os

if __name__ == "__main__":
    # Run Setup.py from the scripts directory
    scripts_dir = os.path.dirname(os.path.abspath(__file__))
    setup_script = os.path.join(scripts_dir, "scripts", "Setup.py")

    result = subprocess.call([sys.executable, setup_script])
    sys.exit(result)
#!/bin/bash

# Get the absolute path to the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Move to the project root (one level up from the scripts folder)
cd "$SCRIPT_DIR/.."

echo "=== Building Hydra Engine (Debug) ==="
# Execute make from the project root
if ! make config=debug; then
    echo "Build failed! Exiting..."
    exit 1
fi

echo "=== Starting Hydra Engine Sandbox ==="
# Change directory to Sandbox to ensure relative asset paths work correctly
pushd Sandbox > /dev/null

# Run the executable relative to the current Sandbox directory
./../bin/Debug-linux-x86_64/Sandbox/Sandbox

# Return to the previous directory
popd > /dev/null

echo "=== Hydra Engine Sandbox exited ==="
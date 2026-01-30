#!/bin/bash

# Hydra Engine Run Script
# This script builds and runs the Sandbox application

echo "=== Building Hydra Engine (Debug) ==="
# Build the project
if ! make config=debug; then
    echo "Build failed! Exiting..."
    exit 1
fi

echo "=== Starting Hydra Engine Sandbox ==="
# Run the executable from the Sandbox working directory so relative asset paths resolve
pushd Sandbox > /dev/null
../bin/Debug-linux-x86_64/Sandbox/Sandbox
popd > /dev/null

echo "=== Hydra Engine Sandbox exited ==="

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
# Run the executable
./bin/Debug-linux-x86_64/Sandbox/Sandbox

echo "=== Hydra Engine Sandbox exited ==="

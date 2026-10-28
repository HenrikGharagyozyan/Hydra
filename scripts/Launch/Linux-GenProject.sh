#!/bin/bash

# Get the absolute path to the scripts folder
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# Navigate to the root of the Hydra project
cd "$SCRIPT_DIR/../.."

# Prefer the Premake binary that scripts/SetupPremake.py downloads, fall
# back to one on PATH.
PREMAKE="vendor/premake/bin/premake5"
if [ ! -x "$PREMAKE" ]; then
    if command -v premake5 &> /dev/null; then
        PREMAKE=premake5
    else
        echo "premake5 not found. Run 'python3 Setup.py' first to download it."
        exit 1
    fi
fi

echo "=== Generating Makefiles ==="
if ! "$PREMAKE" gmake2; then
    echo "Project generation failed! Exiting..."
    exit 1
fi

# Hydra-ScriptCore is a Premake/Mono project (built via the generated Makefile
# below), not an SDK-style project - there is no .csproj, so msbuild/dotnet
# build cannot target it. Pick whichever Mono C# compiler is actually
# installed; Ubuntu's mono packages only ship `mcs`, not `csc`.
if command -v csc &> /dev/null; then
    CSHARP_COMPILER=csc
elif command -v mcs &> /dev/null; then
    CSHARP_COMPILER=mcs
else
    echo "No C# compiler (csc/mcs) found. Install it with: sudo apt install mono-complete"
    exit 1
fi

# Incremental C++ and C# build (only changed files are recompiled)
echo "=== Building Hydra Engine (Debug) ==="
if ! make config=debug CSC="$CSHARP_COMPILER" -j"$(nproc)"; then
    echo "Build failed! Exiting..."
    exit 1
fi

echo "=== Starting Hydra Editor ==="

# Enter the editor working directory for correct asset paths
pushd HydraEditor > /dev/null

# Run the editor
./../bin/Debug-linux-x86_64/HydraEditor/HydraEditor

popd > /dev/null

echo "=== Hydra Editor exited ==="
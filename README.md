# Hydra Engine

![Hydra](Resources/Branding/Hydra_Logo_Text_Light_Square.png)

Hydra is an early-stage interactive application and rendering engine currently supporting **Windows** and **Linux**. Everything inside this repository is being developed progressively as the engine evolves, with a strong focus on clean system design, performance, and extensibility.

---

## Getting Started

Clone the repository using Git, making sure to include all submodules:

```bash
git clone --recursive https://github.com/1HenrikGharagyozyan/Hydra.git
```

> ⚠️ The `--recursive` flag is required to fetch all submodules.

---

## Building

### Windows

**Recommended:** Visual Studio 2022

1. Run the Python setup script to retrieve dependencies:
   ```bash
   python scripts/Setup.py
   ```
2. Generate the Visual Studio solution:
   ```bash
   GenerateProject.bat
   ```
3. Open the `.sln` file and build the project.

---

### Linux (Ubuntu / Debian)

Hydra supports Linux natively via Makefiles and requires the **Vulkan SDK** for shader compilation (SPIR-V).

**Prerequisites**

Ensure you have the Vulkan SDK installed (from the LunarG repository), along with standard build tools:

```bash
sudo apt update
sudo apt install build-essential python3
# Make sure Vulkan SDK is installed for shaderc and spirv-cross
```

**Build Steps**

1. Fetch necessary dependencies:
   ```bash
   python3 scripts/Setup.py
   ```

2. Generate Makefiles using Premake:
   ```bash
   premake5 gmake2
   ```

3. Build the engine and applications:
   ```bash
   make -j$(nproc)
   ```

4. Launch the editor:
   ```bash
   ./scripts/LaunchEditor.sh
   ```

---

## Recent Updates

- **Rendering:** Implemented a modern shader system with SPIR-V cross-compilation and Uniform Buffer Objects (UBOs) for optimized rendering.
- **Build System:** Improved Premake scripts and added Python scripts for automated dependency retrieval.
- **Core:** Added command-line argument parsing.

---

## Roadmap

The goal of Hydra is to build a powerful, scalable 3D engine with modern architecture — expanding capabilities while maintaining a clean and maintainable codebase.

Planned features include:

- Fast 2D rendering (UI, particles, sprites, etc.)
- High-fidelity Physically-Based 3D rendering *(2D expansion comes first)*
- Support for Mac, Android, and iOS
- Native rendering API support (DirectX, Vulkan, Metal)
- Fully featured viewer and editor applications
- Fully scripted interaction and behavior
- Integrated 2D and 3D physics engine
- Procedural terrain and world generation
- Artificial Intelligence systems
- Audio system
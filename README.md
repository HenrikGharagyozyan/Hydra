<div align="center">

<br/>

# Hydra Engine

**An early-stage interactive application and rendering engine**

![Platform](https://img.shields.io/badge/Platform-Linux-informational?style=flat-square&logo=linux&logoColor=white&color=0d1117)
![Graphics](https://img.shields.io/badge/Graphics-Vulkan-red?style=flat-square&logo=vulkan&logoColor=white&color=AC1A1A)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square&logo=cplusplus&logoColor=white&color=00599C)
![Status](https://img.shields.io/badge/Status-Early--Stage-yellow?style=flat-square&color=E6A817)

<br/>

</div>

---

Hydra is an early-stage interactive application and rendering engine currently developed on **Linux**, with Windows and cross-platform support planned for the future. Everything inside this repository is being developed progressively as the engine evolves, with a strong focus on **clean system design**, **performance**, and **extensibility**.

---

## 🚀 Getting Started

Clone the repository using Git, making sure to include all submodules:

```bash
git clone --recursive https://github.com/1HenrikGharagyozyan/Hydra.git
```

> ⚠️ The `--recursive` flag is **required** to fetch all submodules.

---

## 🐧 Linux (Ubuntu / Debian)

Hydra supports Linux natively via Makefiles and requires the **Vulkan SDK** for shader compilation (SPIR-V).

### Prerequisites

Ensure you have the Vulkan SDK installed (from the LunarG repository), along with standard build tools:

```bash
sudo apt update
sudo apt install build-essential python3 vulkan-sdk
```

### Build Steps

**1.** Check environment and retrieve any necessary dependencies:
```bash
python3 scripts/Setup.py
```

**2.** Generate Makefiles using Premake:
```bash
./scripts/Linux-GenProjects.sh
```

**3.** Build the engine and applications:
```bash
make -j$(nproc)
```

**4.** Launch the editor:
```bash
./scripts/LaunchEditor.sh
```

---

## 📦 Recent Updates

| Area | Description |
|------|-------------|
| 🎨 **Rendering** | Implemented a modern shader system with SPIR-V cross-compilation and Uniform Buffer Objects (UBOs) for optimized rendering |
| 🔧 **Build System** | Improved Premake configuration for Linux and added Python/Bash scripts for automated dependency checks and project generation |
| ⚙️ **Core** | Added command-line argument parsing |

---

## 🗺️ Roadmap

The goal of Hydra is to build a **powerful, scalable 3D engine** with modern architecture — expanding capabilities while maintaining a clean codebase.

**Planned features include:**

- [ ] Fast 2D rendering (UI, particles, sprites, etc.)
- [ ] High-fidelity Physically-Based 3D rendering
- [ ] Official support for Windows, Mac, Android, and iOS
- [ ] Native rendering API support (DirectX, Vulkan, Metal)
- [ ] Fully featured viewer and editor applications
- [ ] Fully scripted interaction and behavior
- [ ] Integrated 2D and 3D physics engine
- [ ] Procedural terrain and world generation
- [ ] Artificial Intelligence systems
- [ ] Audio system

---

<div align="center">

*Hydra is under active development — built progressively, designed to last.*

</div>
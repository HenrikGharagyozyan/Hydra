# Changelog

All notable changes to Hydra are documented in this file.

## [1.0.0] - 2026-10-28

Final release. Hydra is feature-complete as a 2D engine with an editor,
physics and C# scripting, and is no longer being developed.

### Added
- Editor controls for every script field type: `float`, `double`, `bool`,
  `char`, signed and unsigned integers of all widths, and `Vector2/3/4`.
  They work for editor-time values and for live values while the scene plays.
- `CHANGELOG.md` and a rewritten `README.md`.

### Fixed
- `Ctrl+D` (duplicate entity) created an empty entity instead of copying
  its components.
- Deleting an entity read its UUID after the entity had been destroyed.
- The editor crashed when saving or playing a scene whose `ScriptComponent`
  referenced a class that doesn't exist.
- Loading a scene with script fields that were removed from the C# class
  asserted instead of skipping them.
- Opening a missing scene file terminated the editor (an uncaught `YAML::BadFile`).
- `byte`/`sbyte` script fields didn't survive a save/load round trip, and C#
  `byte` was mapped to the signed field type.
- `char` script fields were stored as 1 byte, but C# `char` is 2 bytes.
- `Kinematic` couldn't be selected as a Rigidbody 2D body type.
- Scene cameras kept a wrong aspect ratio after *New* or *Open* until the
  viewport was resized.
- *Save As* during Play/Simulate saved the runtime copy of the scene, and
  *New Scene* during Play didn't stop the runtime.
- `Linux-GenProject.sh` didn't generate Makefiles before building.

### Changed
- Removed leftover demo code from `ScriptEngine` and `EditorLayer`, and the
  placeholder child node in the scene hierarchy.
- Per-field reflection logging lowered from `WARN` to `TRACE`.
- Build intermediates and Python bytecode are no longer tracked.

## Earlier development (2025-08 – 2026-08)

Merged through pull requests #1–#14:

- **C# scripting**: Mono embedding, internal calls, `Hydra-ScriptCore` API,
  script components, reflected public fields and field serialization (#9–#14)
- **Editor play modes**: Play / Simulate / Stop with scene copying (#8)
- **Physics**: Box2D v3 integration, box and circle colliders, collider
  visualization, stability fixes (#2, #6)
- **Renderer**: circle and line rendering in the batched 2D renderer (#1, #3–#5)
- **Build**: Premake workspace and Visual Studio 2022 upgrade (#7)
- **Foundation** (before the pull-request workflow): application and layer
  architecture, events, OpenGL renderer with SPIR-V shader cache, EnTT
  scenes, YAML serialization, ImGui editor with gizmos, content browser and
  mouse picking

[1.0.0]: https://github.com/HenrikGharagyozyan/Hydra/releases/tag/v1.0.0

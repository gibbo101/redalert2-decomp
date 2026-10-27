# Historical native reconstruction

Preserved native project before original-target source recovery. Read [the native README](README_NATIVE_20261020.md) for its capabilities and limits. This is not the active root build.

CMake, source, tools, tests and subsystem notes remain together. Preserved historical entrypoints have unchanged contents and assume a project-local `private/` data tree; private inputs/evidence remain at the repository root. Supply explicit data paths when using them. Existing root build caches predate this move and must not be reused as validation. Configure a fresh build beneath this project or the ignored root build directory when native work resumes. No native build was run for this migration.

LICENSE and THIRD_PARTY retain native dependency notices. Original entrypoint snapshots and historical prose keep their original path spellings as evidence. [Migration index](../../docs/NATIVE_ARCHIVE_20261020.md).

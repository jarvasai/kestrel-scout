# CAD handoff — awaiting maker-supplied files

No KESTREL CAD models are included yet. The maker has said they will provide CAD parts. Do not describe these parts as received, reviewed, printable, compatible, or designed by this repository until they are actually supplied and checked.

## How we will process the files

1. Preserve the original files unmodified in `hardware/cad/source/` and add a dated intake record.
2. Record who created each model, the source or upstream URL, revision/date, units, coordinate orientation, intended hardware version, and the exact license/permission to redistribute.
3. Do not publish confidential, personally identifiable, or third-party files without explicit permission and a compatible license. A file being sent privately does **not** automatically authorize a public upload.
4. Validate filenames, file type, units, part dimensions, assembly references, and software/version requirements. Keep supplied originals separate from any edited, derived, converted, or repair files.
5. Export a lightweight preview such as an image or STEP only when allowed by the model license. Preserve original revision IDs and hashes in the intake record.
6. Print a small fit check before publishing a final STL pack. Record slicer, material, settings, and issues; never promise strength from an untested model.

## Current file register

| Filename | Author/source | Revision | Units | License/permission | Review status |
| --- | --- | --- | --- | --- | --- |
| — | Awaiting files from project maker | — | — | — | Not received |

## Preferred formats

- Editable native CAD file plus referenced components/assets.
- STEP (`.step`/`.stp`) neutral solid model for inspection.
- STL/3MF exports only as convenience printing formats, with units and scale verified.
- Include a manifest when a design contains multiple parts or linked references.

Use a dated subfolder for each release, for example `hardware/cad/releases/v0.1/`, only after license and fit review. Keep large binary versions and repeated mesh exports out of Git history when possible; use Git LFS only if the repository setup supports it reliably.

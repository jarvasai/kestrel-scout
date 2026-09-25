# Contributing to KESTREL

Thanks for helping make the project more reproducible. At this stage, the most useful contributions are tested fixes, documentation improvements, sensor research backed by datasheets, and CAD revisions with clear attribution.

## Before opening a change

- Check the [project status](docs/PROJECT_STATUS.md), [roadmap](docs/ROADMAP.md), and [safety notes](docs/SAFETY.md).
- Keep claims proportional to evidence. Mark simulations, concepts, and untested designs as such.
- For code changes, explain the behavior change, include a focused host test, and run the documented `g++ -std=c++11 -Wall -Wextra -Werror` command.
- For hardware/CAD changes, include source/author, revision, units, license/permission, intended board, and a screenshot or reproducible fit/test note.
- Do not include passwords, Wi-Fi credentials, private contact details, purchase receipts with addresses, or battery serial numbers.

## CAD and third-party assets

Only submit files that you created or are authorized to redistribute. Attach or link the license terms and attribution. Do not assume that a file from a vendor listing, another GitHub repository, or a private message is public-domain. Keep unmodified upstream files and KESTREL-specific changes clearly separated.

## Test reports

Use the template in [`docs/TEST_PLAN.md`](docs/TEST_PLAN.md). Include the commit, setup, measured readings, failures, and evidence. Never call a single supervised demonstration a safety certification.

## Conduct

Be kind, specific, and constructive. Critique designs and evidence, not the person. See [`CODE_OF_CONDUCT.md`](CODE_OF_CONDUCT.md).

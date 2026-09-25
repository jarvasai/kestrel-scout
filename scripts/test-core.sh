#!/usr/bin/env sh
set -eu
repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
binary=$(mktemp "${TMPDIR:-/tmp}/kestrel-core-tests.XXXXXX")
trap 'rm -f "$binary"' EXIT HUP INT TERM
cxx=${CXX:-g++}
"$cxx" -std=c++11 -Wall -Wextra -Werror \
  "$repo_root/firmware/kestrel-core/KestrelCore.cpp" \
  "$repo_root/firmware/kestrel-core/tests/test_kestrel_core.cpp" \
  -o "$binary"
"$binary"

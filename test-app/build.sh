#!/usr/bin/env bash
# Usage: ./build.sh <qt-version> [qt-root]   e.g. ./build.sh 6.8.3
set -euo pipefail
ver="${1:?usage: $0 <qt-version> [qt-root]}"
root="${2:-/opt/qt}"
here="$(cd "$(dirname "$0")" && pwd)"
bdir="$here/build-$ver"

cmake -S "$here" -B "$bdir" -G Ninja -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_PREFIX_PATH="$root/$ver/gcc_64"
cmake --build "$bdir"
(cd "$bdir" && LD_LIBRARY_PATH="$root/$ver/gcc_64/lib" QT_QPA_PLATFORM=offscreen ./test_app --smoke)

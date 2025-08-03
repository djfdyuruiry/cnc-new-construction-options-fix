#!/usr/bin/env bash
set -eEuo pipefail

script_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

. "${script_path}/lib/vars.sh"

function main() {
  local cmake_preset="${1}"
  local source="${2}"
  local target="${3}"

  find "${build_path}/${cmake_preset}/RelWithDebInfo" \
    -maxdepth 1 \
    -type f \
    -executable \
    -iname "${source}" \
    -print0 | xargs -0 -I {} cp -fv "{}" "${target}"
}

main "$@"

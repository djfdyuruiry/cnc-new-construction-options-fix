#! /usr/bin/env bash
set -eEuo pipefail

script_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

. "${script_path}/lib/vars.sh"
. "${script_path}/lib/functions.sh"

function main() {
  assert_variable_exists "RA_DATA_PATH" \
    "Set the env var RA_DATA_PATH to a directory that contains Tiberian Dawn game data and try again"

  "${script_path}/1.build.sh" "ra" "$@"
  "${script_path}/2.deploy.sh" "nco-red-alert-debug" "vanillara" "${RA_DATA_PATH}/vanillara-dev"

  pushd_silent "${RA_DATA_PATH}"

  local log_path="${build_path}/vanillara.log"
  start_logging "${log_path}"

  local exit_code=0

  ./vanillara-dev -CHEAT "$@" || {
    exit_code="$?"
    stop_logging
    log_error "Game finished with non-zero exit code: ${exit_code}"
  }

  stop_logging
  log_warning "View full game log: ${log_path}"

  rm "vanillara-dev"
  popd_silent

  exit "${exit_code}"
}

main "$@"

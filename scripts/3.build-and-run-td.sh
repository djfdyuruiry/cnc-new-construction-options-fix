#! /usr/bin/env bash
set -eEuo pipefail

script_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

. "${script_path}/lib/vars.sh"
. "${script_path}/lib/functions.sh"

function main() {
  assert_variable_exists "TD_DATA_PATH" \
    "Set the env var TD_DATA_PATH to a directory that contains Tiberian Dawn game data and try again"

  "${script_path}/1.build.sh" "td" "$@"
  "${script_path}/2.deploy.sh" "nco-tiberian-dawn" "vanillatd" "${TD_DATA_PATH}/vanillatd-dev"

  pushd_silent "${TD_DATA_PATH}"

  local log_path="${build_path}/vanillatd.log"
  start_logging "${log_path}"

  local exit_code=0

  ./vanillatd-dev "$@" || {
    exit_code="$?"
    stop_logging
    log_error "Game finished with non-zero exit code: ${exit_code}"
  }

  stop_logging
  log_warning "View full game log: ${log_path}"

  rm "vanillatd-dev"
  popd_silent

  exit "${exit_code}"
}

main "$@"

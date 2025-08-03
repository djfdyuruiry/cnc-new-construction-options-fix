#! /usr/bin/env bash
set -eEuo pipefail

script_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

. "${script_path}/lib/vars.sh"
. "${script_path}/lib/functions.sh"

function main() {
  "${script_path}/1.build.sh" "td"
  "${script_path}/2.deploy.sh" "nco-tiberian-dawn" "vanillatd" "vanillatd-dev"

  cd "${TD_DATA_PATH}"

  local log_path="${build_directory}/nco-tiberian-dawn/vanillatd.log"
  start_logging "${log_path}"

  ./vanillatd-dev "$@" || {

    echo "Game finished with non-zero exit code: $?"
    echo "View full game log: ${log_path}"

    rm "vanillatd-dev"
    exit 1
  }

  rm "vanillatd-dev"
}

main "$@"

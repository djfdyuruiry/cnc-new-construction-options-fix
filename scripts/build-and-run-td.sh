#! /usr/bin/env bash
set -eEuo pipefail

scriptPath="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

"${scriptPath}/build-ninja.sh" "td"

cd "${TD_DATA_PATH}"
cp -f "${scriptPath}/../build/nco-tiberian-dawn/RelWithDebInfo/vanillatd" "vanillatd-dev"

if [ "${1:-}" == "--no-run" ]; then
  exit 0
fi

./vanillatd-dev "$@" || {
  echo "Game finished with non-zero exit code: $?"

  rm "vanillatd-dev"
  exit 1
}

rm "vanillatd-dev"

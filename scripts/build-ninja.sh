#! /usr/bin/env bash
set -eEuo pipefail

scriptPath="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "${scriptPath}/.."

function runTests() {
  for test in $(find build -maxdepth 1 -type f -executable -wholename 'build/test_*' | tr '\n' ' '); do
    printf "\n\033[1;34mRunning %s\033[0m\n" "${test}"

    "$test" || {
      echo -e "\033[1;31mFAIL\033[0m"
      continue
    }

    echo -e "\033[1;32mPASS\033[0m"
  done
}

function runBuildAll() {
  cmake --workflow --preset "nco"
}

function runBuildRa() {
  cmake --workflow --preset "nco-tiberian-dawn"
}

function runBuildTd() {
  cmake --workflow --preset "nco-tiberian-dawn"
}

function main() {
  local target="${1:-td}"

  case "${target}" in
    ra)
      runBuildRa
      ;;
    td)
      runBuildTd
      ;;
    *)
      runBuildAll
      ;;
  esac

  runTests

  printf '\n\033[1;32m%s\033[0m\n\n' "Executable build output:"
  find "$(pwd)/build" -maxdepth 1 -type f -executable
}

main "$@"

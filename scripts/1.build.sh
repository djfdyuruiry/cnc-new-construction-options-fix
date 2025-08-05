#!/usr/bin/env bash
# shellcheck source-path=SCRIPTDIR
set -eEuo pipefail

script_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

. "${script_path}/lib/vars.sh"
. "${script_path}/lib/functions.sh"

function log_binary_output() {
  local build_output_path="${1}"

  local output_binaries
  output_binaries="$(\
    find "${build_output_path}" \
      -maxdepth 1 \
      -type f \
      -executable \
      | grep -v "test_" \
      | tr '\n' '\t' \
  )"

  log_info "Binaries created by build: %s" "${output_binaries}"
}

function run_tests() {
  local build_output_path="${1}"

  local failed_tests=""

  log_info "Executing test binaries"

  for test in $(find "${build_output_path}" -maxdepth 1 -type f -executable -wholename "${build_output_path}/test_*" | tr '\n' ' '); do
    log_warning "Running test: ${test}"

    "$test" || {
      log_error "Test FAILED"
      failed_tests="${failed_tests} ${test}"

      continue
    }

    log_info "Test PASSED"
  done

  if [ -n "${failed_tests}" ]; then
    log_error "Test FAILURES detected:${failed_tests}"
    return 1
  fi
}

function build_and_test() {
  local cmake_preset="${1}"
  local build_output_path="${2}"

  shift 2

  local log_file_path="${build_path}/nco-build.log"
  start_logging "${log_file_path}"

  pushd_silent "${repo_path}"

  log_warning "Executing: cmake --workflow --preset ${cmake_preset} $*"

  cmake --workflow --preset "${cmake_preset}" "$@" || {
    local exit_code="$?"

    stop_logging
    log_error "Build failed, see log file: ${log_file_path}"

    exit "${exit_code}"
  }

  run_tests "${build_output_path}" || {
    local exit_code="$?"

    stop_logging
    exit "${exit_code}"
  }

  stop_logging
}

function main() {
  local target="${1:-all}"

  # Shift the first argument to use as target, but keep it for cmake call later
  shift

  export CC="clang"
  export CXX="clang++"
  export VC_CXX_FLAGS="-w;-Wwrite-strings;-Werror=write-strings"

  local cmake_preset="nco"

  case "${target}" in
    ra)
      cmake_preset="nco-red-alert"
      ;;
    td)
      cmake_preset="nco-tiberian-dawn"
      ;;
  esac

  local build_output_path="${build_directory}/${cmake_preset}/RelWithDebInfo"

  build_and_test "${cmake_preset}" "${build_output_path}" "$@"
  log_binary_output "${build_output_path}"
}

main "$@"

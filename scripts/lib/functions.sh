#! /usr/bin/env bash
# shellcheck source-path=SCRIPTDIR
set -eEuo pipefail

lib_scripts_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

. "${lib_scripts_path}/vars.sh"

function pushd_silent() {
  pushd "$@" &> /dev/null
}

function popd_silent() {
  popd &> /dev/null
}

function stop_logging() {
  exec > /dev/tty 2>&1
}

function start_logging() {
  local logFile="${1}"

  exec > >(tee -ia "${logFile}") 2>&1
}

function _log_with_color() {
  local level="${1}"
  local color="${2}"
  local message="${3}"

  shift 3

  local timestamp
  timestamp="$(date --iso-8601=seconds)"

  local formatted_message
  # shellcheck disable=SC2059
  formatted_message="$(printf "${message}" "$@")"

  printf "\e[${color}m[%s] %s: %s\e[0m\n" \
    "${level}" \
    "${timestamp}" \
    "${formatted_message}"
}

# Log functions for different levels
function log_trace() {
  _log_with_color "TRACE" "90" "$@" # Light gray for TRACE
}

function log_debug() {
  _log_with_color "DEBUG" "34" "$@" # Blue for DEBUG
}

function log_info() {
  _log_with_color "INFO" "32" "$@" # Green for INFO
}

function log_warning() {
  _log_with_color "WARNING" "33" "$@" # Yellow for WARNING
}

function log_error() {
  _log_with_color "ERROR" "31" "$@" # Red for ERROR
}

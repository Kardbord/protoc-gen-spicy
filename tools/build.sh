#!/usr/bin/env bash
set -e

function usage() {
  echo "${0##*/}"
  echo
  echo "Usage"
  echo "  ${0##*/} [-h] [-c] [-b <Debug|Release>]"
  echo
  echo "Options"
  echo "  -h            Prints this usage"
  echo "  -b BUILD_TYPE Selects the build type <Debug|Release>"
  echo "  -c            Performs a clean build."
}

CLEAN=false
BUILD_TYPE="Release"
EXTRA_CMAKE_OPTS=
while getopts ":hb:c" opt; do
  case "${opt}" in
  b)
    BUILD_TYPE="${OPTARG}"
    ;;
  c)
    CLEAN=true
    ;;
  h)
    usage
    exit 0
    ;;
  *)
    usage
    exit 1
    ;;
  esac
done
shift $((OPTIND - 1))

if ! [[ "${BUILD_TYPE}" =~ ^(Debug|Release)$ ]]; then
  echo "Unknown build type: ${BUILD_TYPE}"
  usage
  exit 1
fi

mkdir -p "$(dirname "${BASH_SOURCE[0]}")/../build"
pushd "$(dirname "${BASH_SOURCE[0]}")/../build" >/dev/null
if [[ "${CLEAN}" = "true" ]]; then
  find . ! -name 'README.md' ! -name '.' -delete
fi
cmake -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" "${EXTRA_CMAKE_OPTS}" .. && make
popd >/dev/null

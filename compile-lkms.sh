#!/usr/bin/env bash

set -e

TMP_PATH="/tmp"
DEST_PATH="./output"
TOOLKIT_VER="7.1"

mkdir -p "${DEST_PATH}"

function compileLkm() {
  PLATFORM=$1
  KVER=$2
  OUT_PATH="${TMP_PATH}/${PLATFORM}"
  mkdir -p "${OUT_PATH}"
  sudo chmod 1777 "${OUT_PATH}"
  docker run -u 1000 --rm -t -v "${OUT_PATH}":/output -v "${PWD}":/input \
    andatoshiki/shiki-compiler:${TOOLKIT_VER}-ubuntu-amd64 compile-lkm ${PLATFORM}
  mv "${OUT_PATH}/shiki-dev.ko" "${DEST_PATH}/shiki-${PLATFORM}-${KVER}-dev.ko"
  rm -f "${DEST_PATH}/shiki-${PLATFORM}-${KVER}-dev.ko.gz"
  gzip "${DEST_PATH}/shiki-${PLATFORM}-${KVER}-dev.ko"
  mv "${OUT_PATH}/shiki-prod.ko" "${DEST_PATH}/shiki-${PLATFORM}-${KVER}-prod.ko"
  rm -f "${DEST_PATH}/shiki-${PLATFORM}-${KVER}-prod.ko.gz"
  gzip "${DEST_PATH}/shiki-${PLATFORM}-${KVER}-prod.ko"
  rm -rf "${OUT_PATH}"
}

# Main
docker pull andatoshiki/shiki-compiler:${TOOLKIT_VER}-amd64
while read PLATFORM KVER; do
  compileLkm "${PLATFORM}" "${KVER}" &
done < PLATFORMS
wait
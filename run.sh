#!/bin/bash
set -e

BUILD_DIR=build

usage() {
  echo "Uso: $0 [-t|-r]"
  echo "  -t  Ejecutar tests"
  echo "  -r  Ejecutar juego principal"
  exit 1
}

if [ $# -eq 0 ]; then
  usage
fi

# Configurar y compilar
cmake -S . -B "$BUILD_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD_DIR"

while getopts "tr" opt; do
  case $opt in
  t)
    echo "Ejecutando tests..."
    "$BUILD_DIR/tests"
    ;;
  r)
    echo "Ejecutando juego principal..."
    "$BUILD_DIR/juego"
    ;;
  *)
    usage
    ;;
  esac
done

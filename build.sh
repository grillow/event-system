#!/usr/bin/env bash

SCRIPT_PATH="$(realpath $0)"
SCRIPT_DIR_PATH="$(dirname $SCRIPT_PATH)"

BUILD_PATH="$SCRIPT_DIR_PATH/build"
BIN_PATH="$SCRIPT_DIR_PATH/bin"

# [ -e $BUILD_PATH ] && rm -r $BUILD_PATH/*
mkdir -p $BUILD_PATH
cd $BUILD_PATH
time cmake .. || exit 1
time make || exit 1
time make test || exit 1
time valgrind --error-exitcode=1 --leak-check=full $BIN_PATH/Test


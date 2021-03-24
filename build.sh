#!/usr/bin/env bash

BUILD_PATH="build"

# [ -e $BUILD_PATH ] && rm -r $BUILD_PATH/*
mkdir -p $BUILD_PATH
cd $BUILD_PATH
time cmake ..
time make
time make test


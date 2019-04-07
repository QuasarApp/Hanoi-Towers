#!/bin/sh

BASE_DIR=$(dirname $0)
TARGET_DIR="$BASE_DIR/installer/packages/HanoiTowers/data"
echo "selected target dir $TARGET_DIR"
echo "cd to snapcraft dir $BASE_DIR"
cd $BASE_DIR

snapcraft


#!/bin/sh
OLD_DIR=$PWD
BASE_DIR=$(dirname $0)
TARGET_DIR="$BASE_DIR/../../"
echo "selected target dir $TARGET_DIR"
echo "cd to snapcraft dir $BASE_DIR"
cd $BASE_DIR

snapcraft

echo "return to old dir $OLD_DIR"
cd $OLD_DIR

rm -f $TARGET_DIR/*.snap
mv $BASE_DIR/*.snap $TARGET_DIR

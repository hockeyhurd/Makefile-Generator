#!/bin/bash

CC="CC=g++"
CFG=""

# Get variables passed
for var in "$@"
do
    if [ ${var:0:10} == "CC=clang++" ]
    then
        CC="$var"
    elif [ ${var:0:6} == "CC=g++" ]
    then
        CC="$var"
    elif [ $var == "CFG=Debug" ]
    then
        CFG="$var"
    elif [ $var == "CFG=Release" ]
    then
        CFG="$var"
    else
        echo "Unrecognized command $var"
        exit -1
    fi
done

# echo "CC=$CC"
# echo "CFG=$CFG"

pushd src > /dev/null

time make $CC $CFG

popd > /dev/null

#!/bin/bash

pushd src > /dev/null

./makegen -type cpp -name FakeMakefile -cflags "-pipe -std=c++17 -g -O0 -Wall -Wextra -pedantic" -o "test" -src "Test.cpp"

popd > /dev/null

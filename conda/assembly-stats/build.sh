#!/bin/bash

mkdir build
cd build

cmake .. \
      -DCMAKE_INSTALL_PREFIX=$PREFIX \
      -DCMAKE_PREFIX_PATH=$PREFIX \
      -DASMSTATS_ENABLE_TESTS=OFF

cmake --build . --config Release --target install
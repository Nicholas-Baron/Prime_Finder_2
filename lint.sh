#!/bin/bash

cppcheck --output-file=lint.txt --check-config --suppress=missingIncludeSystem --enable=all -x c++ src/

cppcheck --output-file=lint.txt --enable=all --suppress=missingIncludeSystem -x c++ src/

#!/bin/bash
doc8 README.rst
pushd docs
doc8 source/
rm -rf build
sphinx-build -E -W --color -b html -d build/doctrees source build/html
sphinx-build -E -W --color -b linkcheck -d build/doctrees source build/html
popd

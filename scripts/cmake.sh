#!/usr/bin/env bash

set -euo pipefail

cmake -DCMAKE_BUILD_TYPE=Release -B build -G Ninja

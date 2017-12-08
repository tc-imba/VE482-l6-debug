#!/usr/bin/env bash

name=${1%%.c}
diff ${name}.c ${name}.debug.c > ${name}.c.diff
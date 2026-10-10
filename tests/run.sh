#!/bin/bash

cc=clang

$cc test.c -o out
./out
rm -rf out

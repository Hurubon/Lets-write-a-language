#!/bin/bash
clang -target i686-pc-windows-gnu -pedantic -ansi
src/errors/errors.c
src/file_adapter/file_adapter.c
src/zfind_algorithm/zfind_algorithm.c
src/lexer/lexer.c
src/main.c
-o main.exe
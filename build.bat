@echo off
gcc main.c -o crainfuck.exe -Wall -Os -static
strip crainfuck.exe
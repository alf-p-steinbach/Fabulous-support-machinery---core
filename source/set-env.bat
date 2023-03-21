@echo off
call set-gcc-path
call vcvars64
set cpath=d:\root\dev\include
set _i=%include%
set include=%_i%;%cpath%

taamath
=======

author:  Thomas Atwood (tatwood.net)
date:    2011
license: see UNLICENSE.txt

This is a collection of C headers that provide inlined functionality for
linear math operations. This is a header only library, no link target is
required for its use.

Building
========

Limited support for VPU intrinsics exists. Currently, this only includes SSE3
on x86 and x64. The following macro can be defined to disable VPU support and
revert to the FPU fallback implementations:
    taa_MATH_FPU

## Linux ###
The the following dependencies are required to build on Linux:
    taasdk
    -lm

### Windows ###
The the following dependencies are required to build on Microsoft Windows:
    taasdk 


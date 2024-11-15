# libgba
libgba is a C library for the Gameboy Advance which contains full register/structure definitions for the GBA hardware, as well as some additional functionality which is useful for application development. This extra functionality includes:

- C wrappers for [BIOS functions](https://problemkaputt.de/gbatek.htm#biosfunctions): division, square root, decompression, etc
- A text console with printf support and ANSI color escape codes

The best place to find usage examples is in the [gba-examples](https://github.com/devkitPro/gba-examples) repository. libgba is also included (along with the examples) in the [devkitPro](https://devkitpro.org/wiki/Getting_Started) toolkit for GBA development.

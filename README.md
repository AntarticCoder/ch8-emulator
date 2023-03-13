# Ch8 Emulator

## Overview

Chip 8 was a virtual interpreter that was developed in the mid 1970's by Joseph Weisbecker and was used to be able to run games on all different types of computers. Chip 8 can run a variety of games like 'Pong', 'Space Invaders', and many more. Today, Chip 8 is used as a learning excersize to begin the journey of emulation development, and is a great way to start with low level programming.

## Screenshots

![Alt text](/images/IBM_Chip_8_Screenshot.png?raw=true "IBM Logo")

## TODO

- [X] Implement all 34 opcodes
- [X] Draw graphics to an SDL window
- [ ] Implement Sound
- [ ] Add CLI interface to load roms and customize the settings
- [ ] Add visual debugger to view registers, memory, and debug both the emulator and rom

## Credits

### ROMS

* [Chiptest - A small rom that provides easy test for early development of a Chip 8 emulator.](https://github.com/offstatic/chiptest)
* [IBM - A rom that draws the IBM logo](https://github.com/loktar00/chip8)
* [Chip 8 Test Rom - A small rom that checks if all the opcodes are working as expected](https://github.com/corax89/chip8-test-rom)

### Articles

* [BUILDING A CHIP-8 EMULATOR [C++] by Austin Morlan](https://austinmorlan.com/posts/chip8_emulator/)
* [Guide to making a CHIP-8 emulator by Tobias V. Langhoff](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)

### Documentation

* [Wikipedia](https://en.wikipedia.org/wiki/CHIP-8)
* [Cowgod's Chip-8 technical reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
* [Columbia University's Chip-8 Design Specification](http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf)
# A Bit Lost

A Bit Lost is a simple puzzle game run from the command line. Help a lost bit escape a sea of bytes, using the bitwise operations AND and XOR to advance and get the correct bit values through the exits.

A Bit Lost is an entry for 2022's C Jam on itch.io (https://itch.io/jam/c-jam), commemorating the 50th anniversary of the C programming language. The theme for the jam was "bitwise."

## Building

### macOS, Linux, and Other Unices

To build and run A Bit Lost in a Unix-like environment, install `make` and a C compiler (e.g., `gcc`, `clang`), clone and navigate to the `abitlost` repo, and run the following in an ANSI-compatible terminal:

```
cd src
make
.\abitlost
```

### Windows

A Bit Lost requires a POSIX-compatible environment. Either Windows Subsystem for Linux (WSL) or Cygwin (https://www.cygwin.com/) will work for building and running. The instructions above for Unix-like environments apply when using these options.

### Command-Line Flags

- `--no-color` or `-n`: disable color
- `--level n` or `-l n`: start at level _n_, where _n_ is a whole number greater than 0

## Playing

### Objective

Starting with a lone bit at the top of the play area, get the necessary bit values through the exits at the bottom, using the bitwise operations AND and XOR (exclusive OR) to advance. Each operation applies to your current byte row (marked by an arrow) and the next row, replacing the latter. Upon reaching the bottom row, if the bit values match the exits (`1` -> `O`, `0` -> `X`), you win the level and advance to the next. Each level adds either additional rows to navigate or additional exits to reach.

For more information on bitwise AND and XOR, see the Wikipedia entry on bitwise operations at <https://en.wikipedia.org/wiki/Bitwise_operation>.

### Controls

- a or &: bitwise AND
- x or ^: bitwise XOR (exclusive OR)
- r: reset the level
- n: next level (after beating the current level)
- q: quit

## Known Issues

Building on Windows throws warnings about implicit declarations for `srandom` and `random`, but otherwise seems to compile and run fine.

## Copyright and License Notices

Copyright (C) 2022 Jesse Douglas (jesse@jessedouglas.net).

A Bit Lost is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.

Binary distributions for Windows may include object files from the Cygwin project. The Cygwin DLL and utilities are copyright (C) Cygwin authors. Source code and licensing terms for the Cygwin project are available at <https://cygwin.com/>.

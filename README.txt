==================================================

  Project Name  : Ceasar's code demonstration
  Version       : 1.0
  Author        : Romain Croughs
  Date          : 2024-02-10
  Description   : Tools to understand & test
                  the Caesar's code

==================================================
                     CONTENTS
==================================================

  1. Introduction
  2. Installation
  3. Usage
  4. License

==================================================
                 1. INTRODUCTION
==================================================

  The Ceasar's code is a simple encryption method
  where each letter of the alphabet is shifted
  by a fixed number of positions down the alphabet.
  This project provides tools to encode and decode,
  and a bash file to show the ease of cracking the
  code.

  This project is intended for educational purposes
  for children of ~12 years of age.

==================================================
                 2. INSTALLATION
==================================================

  Compile the project with the following command:
    $ make
  And give execution rights to the bash file:
    $ chmod +x demo.sh

==================================================
                   3. USAGE
==================================================

  encoding:
    ./encode "your message" [shift]
    if no shift is provided, all possible shifts
    are showed.
    if no message is provided, an interactive
    mode is launched.
  decoding:
    ./decode "your message" [shift]
    if no shift is provided, all possible shifts
    are showed.
    if no message is provided, an interactive
    mode is launched.
  demonstration:
    ./demo.sh

==================================================
                   4. LICENSE
==================================================

  No license is provided for this project.
  Feel free to use, modify and distribute it.

==================================================


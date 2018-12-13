# Connect-Four-AI
The popular board game Connect Four implemented in C++ using SFML graphics. By default, the program has an AI hint that's implemented using Monte Carlo Tree search that utilizes multi-core processing.

# Requirements:
G++ with C++14 or newer
SFML libraries
Pthread

# How to run?
g++ -std=c++14 src.cpp Board.cpp Board.h -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -pthread

# Command-line Arguments?
Currently unimplemented
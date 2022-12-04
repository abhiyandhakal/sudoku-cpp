#!/bin/bash

sed -i '14d' ./include/DEFINITIONS.hpp

sudo rm /usr/local/bin/sudoku
sudo rm $HOME/.local/share/applications/sudoku.desktop
#!/bin/bash

if grep -q PATH "include/DEFINITIONS.hpp"; then
  echo "The script has already run, it cannot run it again."
  echo "To run it again, replace the last line of include/DEFINITIONS.hpp by a new line"
else
  # installing library
  which apt >/dev/null 2>&1
  if [ $? -eq 0 ]
  then
      sudo apt install libsfml-dev
  fi
  which dnf >/dev/null 2>&1
  if [ $? -eq 0 ]
  then
      sudo dnf install SFML-devel
  fi
  which pacman >/dev/null 2>&1
  if [ $? -eq 0 ]
  then
      sudo pacman -S sfml
  fi

  echo "#define PATH \"${PWD}/\"" >> include/DEFINITIONS.hpp
  make clean
  make

  sudo cp bin/sudoku /usr/local/bin/

  echo "[Desktop Entry]" > sudoku.desktop
  echo "Encoding=UTF-8" >> sudoku.desktop
  echo "Type=Application" >> sudoku.desktop
  echo "Terminal=false" >> sudoku.desktop
  echo "Name=Sudoku" >> sudoku.desktop
  echo "Exec=sudoku" >> sudoku.desktop
  echo "Icon=$PWD/assets/images/icon.png" >> sudoku.desktop
  echo "Version=1.0" >> sudoku.desktop

  sudo mv sudoku.desktop $HOME/.local/share/applications

  sudo chmod 777 db/
  sudo chmod 777 db/*

  echo "hello world"
fi
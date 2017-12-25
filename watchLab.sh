#!/bin/bash

while true; do
  if g++ *.cpp -o lab; then
    ./lab
  fi
  inotifywait -e modify *.cpp;
done
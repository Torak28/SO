#! /bin/bash/

awk '{total += $1} END {print total}' $1

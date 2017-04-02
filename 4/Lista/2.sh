#! /bin/bash/

echo "wikimedia" | tr "mw" "pW"
# Zamieni mw na pW

echo "wiki" | tr -d "ki"
#Usunie wszystkie i,k

cat $1 | tr a-z A-Z
#Zamienia male litery na wielkie

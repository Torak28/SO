#! /bin/bash/

echo Niepowtarzalne:
cat $1 | sort | uniq

echo Powtarzajace sie wiecej niz raz:
cat $1 | sort | uniq -d

echo Powtórzone raz:
cat $1 | sort | uniq -u

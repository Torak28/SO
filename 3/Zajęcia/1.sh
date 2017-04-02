#! /bin/bash

#W zadanym drzewie katalogu dla plików regularnych o rozszerzeniu .png i rozmiarze
#ponieżej 100 bajtów wypisać rozmiar w bajtach, a dla plików do których ich
#właściciel grupy nie ma prawa zapisu i wykonania wypisać właściciela grupowego.

if [ $# -eq 1 -a -d $1 ]
then
	find $1 -type f -name "*.png" -size -100c -printf "Mniejsze niz 100B %p %s B\n" -o ! -perm /030 -printf "GID bez wx %p %G \n"
fi

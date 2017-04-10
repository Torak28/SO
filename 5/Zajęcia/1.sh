#! /bin/bash

#W zadanym drzewie katalogów wypisać nazwy plików, dla których katalog nadrzędny
#nazywa się "parent" lub które mają rozszerzenie txt. Dodatkowo wypisać liczbę 
#takich plików. Potok find | awk

if [ $# -eq 1 -a -d $1 ]
then
	find $1 -print | awk -F/ '{if($(NF-1)=="parent" || substr($NF,length($NF)-3)==".txt") print $0 ilosc++} END{print ilosc}'
fi


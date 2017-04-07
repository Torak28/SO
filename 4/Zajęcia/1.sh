#! /bin/bash

#Dane jest drzewo katalogowe. Do każdego katalogu w tym drzewie wypisać jego nazwe oraz liczbe ukrytych plików, a dla każdego pliku regularnego nazwe, oraz długość ostatniego członu nazwy(w znakach). Wynik posortować wg. liczb.

if [ $# -eq 1 -a -d $1 ]
then
	find $1 ! -name $1 -type d -printf "K %p\n" -or -type f -printf "P %p\n" | while read typ nazwa
	do
		if [ $typ = "P" ]
		then
			numer=`basename $nazwa | wc -m`
			numer=$((numer-1))
			echo $numer $typ $nazwa
		fi
		if [ $typ = "K" ]
		then
			numer=`ls -ad $nazwa/.* | wc -l`
			numer=$((numer-2))
			echo $numer $typ $nazwa
		fi
	done | sort -n -r
fi

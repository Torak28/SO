#! /bin/bash

#Dane jest drzewo katalogowe. Do każdego katalogu w tym drzewie wypisać jego nazwe oraz liczbe ukrytych plików, a dla każdego pliku regularnego nazwe, oraz długość ostatniego członu nazwy(w znakach). Wynik posortować wg. liczb.

if [ $# -eq 1 -a -d $1 ]
then
	#find $1 -type d ! -name $1 #lista katalogow A1
	#find $wynikA1 -type f -name ".*" | wc -l#Liczy ukryte pliki
	#find $1 -type f #lista plikow A2
	#basename $wynikA2 | wc -m #liczy znaki +1	
	find $1 ! -name $1 -type d -printf "k %p\n" -or -type f -printf "p %p\n" | while read var1 var2
	do
		if [ $var1 = "p" ]
		then
			var3=`basename $var2 | wc -m`
			echo $var1 $var2 $var3
		fi
		if [ $var1 = "d" ]
		then
			var3=`ls -d $var2/.* | wc -l`
			echo $var1 $var2 $var3
		fi
	done
fi

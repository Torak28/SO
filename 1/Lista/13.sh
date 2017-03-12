#! /bin/bash/

#Usuwanie  z  zadanego  katalogu  (pierwszy  argument  skryptu)  wszystkich  plików,  których  
#nazwy   pokrywają  się  z   nazwami   w   drugim   katalogu   (drugi   argument).   Nie   usuwaj   
#podkatalogów.   Nie   usuwaj   również  plików   o   nazwach   pokrywających   się   z   nazwami   
#podkatalogów w drugim katalogu. 


echo Usuwanie pliczków z $1 których nazwy pokrywają się z $2

for fileA in `ls $1`;do
	JEST=0
	for fileB in `ls $2`;do
		if [ -f "$1"/$fileA -a -f "$2"/$fileB ]
		then
			if [ $fileA = $fileB ]
			then
				JEST=1
			fi
		fi
	done
	if [ $JEST -eq 1 ]
	then
		echo Usuwam $fileA w $1
		rm "$1"/$fileA
	fi
done

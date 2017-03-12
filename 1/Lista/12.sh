#! /bin/bash/

#Usuwanie   wszystkich   podkatalogów   zadanego   katalogu   (parametr   wywołania   skryptu).   
#Zawartość tych podkatalogów należy przenieść do katalogu nadrzędnego. Usuwanie dotyczy tylko
#jednego poziomu podkatalogów.

echo Usuwam wszystkie podkatalogi z $1 przenosząc ich zawartość do $1

#if [ ! -d WYNIK ]
#then
#	mkdir WYNIK
#fi

for file in $1/*;do
	if [ -d $file ]
	then
		echo Przenoszę zawartośc $file do $1, usuwając $file
		mv $file/* $1
		rmdir $file
	fi
done 

#Komendy:
# mv - przenoszenie
# rmdir - rm na katalogu

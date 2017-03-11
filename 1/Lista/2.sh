#! /bin/bash

#Tworzenie  nowych  plików  w  zadanym  katalogu  (parametr  wywołania skryptu), według 
#listy umieszczonej  w  pliku  (drugi  parametr  wywołania  skryptu).  Nowe  pliki  mają
#być zerowej  wielkości (puste). Jeżeli jakiś plik już istnieje, to nie powinien zostać
#zniszczony.

echo Tworzenie plikow z pliku $2 w miejscu $1

for file in `cat $2`; do
	if [ -f "$1"/$file ]
	then
		echo $file - Taki plik juz istnieje
	else
		echo Tworze nowy plik $file
		touch $1/$file
	fi
done  

#Komendy
#touch - tworzy plik
#[ -f ] - test po plikach

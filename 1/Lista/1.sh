#! /bin/bash

#Zmiana  nazw  wszystkich  plików  w  zadanym  katalogu  (parametr  wywołania  skryptu),  do  
#których mamy ustawione prawo zapisu, przez dopisanie dodatkowego członu .old. Wcześniej należy
#skasować wszystkie pliki, które już mają takie rozszerzenie. 

#Parametr
echo Przekazany parametr: $1 

#Kasowanie:
for file in $1/*.old; do
	echo Usuwam $file
	rm $file -f
done

#Zmiana Nazwy:
for file in $1/*; do
	echo Zmieniam nazwe $file
	mv $file $file.old 
done

#Komendy
#mv - zmiana nazwy
#rm - usuwanie

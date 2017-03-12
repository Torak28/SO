#! /bin/bash/

#Łączenie  w  jeden  plików  z  listy,  umieszczonej    w  pliku  o  zadanej  nazwie  (parametr  
#wywołania  skryptu.  Kolejność,  w  jakiej  pliki  zostaną połączone  -  ściśle  według  listy.
#Treść każdego pliku powinna być poprzedzona nagłówkiem z jego nazwą. Plik wynikowy powinien 
#mieć nazwę pliku pierwotnie zawierającego listę

echo Łaczenie plików z $1 zgodnie z listą z $2. Cąłość capisana w $1 w pliku $2

PLICZKI=$1/$2
touch $PLICZKI

for file in `cat $2`; do 
	if [ -f "$1"/$file -a "$1"/$file != $PLICZKI ]
	then
		echo Zapisywanie $file w $PLICZKI
		echo $file >> $PLICZKI
		cat "$1"/$file >> $PLICZKI
		echo "" >> $PLICZKI
	fi
done

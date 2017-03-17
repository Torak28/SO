#!/bin/bash

#Jarosław Ciołek-Żelechowski, 218386

#Kasowanie wszystkich plików pustych (o zerowej wielkości) w zadanym katalogu (parametr wywołania
#skryptu).  Skrypt  powinien  tworzyć  w  zadanym  pliku  listę  skasowanych  plików.  Nie powinien
#analizować dołączeń symbolicznych.

WYNIK=$2

if [ $# -eq 2 ]
then	
	echo Kasuje pliki puste w $1
	if [ -e $WYNIK -a ! -f $WYNIK ]
	then
		exit 1
	else
		echo -n "" > $WYNIK
	fi

	for file in `ls -a $1`;do
		if [ -f $1/$file -a ! -s $1/$file -a ! -L $1/$file ]
		then
			echo Kasuje plik $file
			echo $1/$file >> $WYNIK
			rm -rf $1/$file
		fi
	done 
fi

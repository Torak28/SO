#!/bin/bash

# Wypisac na ekran wszystkie linki symboliczne
# z danego katalogu (1-szy argument skryptu),
# ktore wskazuje na zadane miejsce (sciezke)
# w systemie plikow (2-gi argument).
# Zadane miejsce moze znajdowac sie poza zadanym katalogiem

if [ "$#" -ne 2 ]
then
        echo "Nope!"
        exit 1
fi

if [ ! -d $1 ]
then
        echo "Nope2!"
        exit 1
fi

for file in `ls -A $1`; do
	if [ -L $1/$file -a `readlink -f $1/$file` = `readlink -f $2` ]
	then
		echo $file jest linkiem symbolicznym do $2
	fi
done

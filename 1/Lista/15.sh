#! /bin/bash/

#Policzenie wszystkich plików w zadanym katalogu (parametr wywołania skryptu), do których 
#ustawione jest prawo dostępu do wykonania („execute”). 

echo Licze w $1 ilosc plików "execute"

LICZBA=0

for file in $1/*;do
	if [ -f $file -a -x $file ]
	then
		echo $file jest "execute"
		LICZBA=`expr $LICZBA + 1`
	fi
done

echo Takich plików jest $LICZBA

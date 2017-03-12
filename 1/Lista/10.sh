#! /bin/bash/

#Porównanie  zawartości  dwóch  zadanych  katalogów  (argumenty  skryptu).  Przy  porównaniu  
#należy ignorować podkatalogi. W wyniku wyświetlić na ekranie listę plików o identycznych 
#nazwach w obu katalogach. 

echo Wypisanie plikow o identycznych nazwach w katologu: $1 i $2

for fileA in `ls $1`; do
	for fileB in `ls $2`; do
		if [ -f "$1"/$fileA -a -f "$2"/$fileB -a $fileA = $fileB ]
		then
			echo $fileA jest w katalogu $1 i $2
		fi
	done 
done

#Komendy
# $A = $B - jako sprawdzenie czy są takie same nazwy

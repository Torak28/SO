#! /bin/bash/

#Ustawienie  na  aktualny  czasu  ostatniej  modyfikacji  wszystkich  plików  zadanego  katalogu  
#(parametr wywołania skryptu), do których mamy prawo dostępu do zapisu/modyfikacji. 

echo Zmieniam czs ostatniej modyfikacji na aktualny w $1

for file in $1/*;do
	if [ -f $file ]
	then
		echo Zmieniam czas $file
		touch -m $file
	fi
done 
